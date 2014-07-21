if $server_values == undef {
  $server_values = hiera('server', false)
}

$www_domain = hiera('domain', 'hackdinium.dev')

Class['apt::update'] -> Package <|
    title != 'python-software-properties'
and title != 'software-properties-common'
|>

Exec { path => [ '/bin/', '/sbin/', '/usr/bin/', '/usr/sbin/', '/usr/local/bin', '/usr/local/sbin' ] }

Wget::Fetch { cache_dir   => '/var/cache/wget' }

include apt

if ! defined(Package['augeas-tools']) {
  package { 'augeas-tools':
    ensure => present,
  }
}

group { 'puppet':   ensure => present }
group { 'www-data': ensure => present }
group { 'www-user': ensure => present }

user { [ 'nginx', 'www-data']:
  shell  => '/bin/bash',
  ensure => present,
  groups => 'www-data',
  require => Group['www-data']
}

user { $::ssh_username:
  shell   => '/bin/bash',
  home    => "/home/${::ssh_username}",
  ensure  => present,
  groups  => [ 'www-data', 'www-user' ],
  require => [ Group['www-data'], Group['www-user'] ]
}

file { "/home/${::ssh_username}":
  ensure => directory,
  owner  => $::ssh_username,
}

# copy dot files to ssh user's home directory
exec { 'dotfiles':
  cwd     => "/home/${::ssh_username}",
  command => "cp -r /vagrant/puppet/files/dot/.[a-zA-Z0-9]* /home/${::ssh_username}/ \
              && chown -R ${::ssh_username} /home/${::ssh_username}/.[a-zA-Z0-9]* \
              && cp -r /vagrant/puppet/files/dot/.[a-zA-Z0-9]* /root/",
  onlyif  => 'test -d /vagrant/puppet/files/dot',
  returns => [0, 1],
  require => User[$::ssh_username]
}

if is_array($server_values['packages']) and count($server_values['packages']) > 0 {
  each( $server_values['packages'] ) |$package| {
    if ! defined(Package[$package]) {
      package { "${package}":
        ensure => present
      }
    }
  }
}

include '::mongodb::server'
include 'scala'

class { 'nginx': }
class { 'ntp': }

file { '/var/www': 
  ensure => 'directory'
}

class { "hhvm":
  compile_from_source => false,
  port                => 9001,
  date_timezone       => "America/Los_Angeles",
  require             => File['/var/www/']
}

exec { 'hhvm-files':
  cwd     => "/home/${::ssh_username}",
  command => "cp -r /vagrant/puppet/files/hhvm/[a-zA-Z0-9]* /etc/hhvm/",
  onlyif  => 'test -d /vagrant/puppet/files/hhvm',
  returns => [0, 1],
  require => User[$::ssh_username]
}
 
# Setting auto_update to true will cause issues with hhvm.
# To update composer, just remove the binary and reload --provision.
class { 'composer':
  auto_update => false,
  require     => Class['hhvm']
}

wget::fetch { 'composer-bash-completion':
  source      => 'https://raw.githubusercontent.com/iArren/composer-bash-completion/master/composer',
  destination => '/etc/bash_completion.d/composer',
  cache_file  => 'composer',
  require     => Class['composer']
}

file { [ '/usr/bin/.lib' , '/usr/bin/.lib/0.13.1' ]:
  ensure => 'directory',
  owner  => 'root',
  group  => 'root'
}

wget::fetch { 'sbt-launch':
  source      => 'http://typesafe.artifactoryonline.com/typesafe/ivy-releases/org.scala-sbt/sbt-launch/0.13.1/sbt-launch.jar',
  destination => '/usr/bin/.lib/0.13.1/sbt-launch.jar',
  cache_file  => 'sbt-launch.jar',
  require     => File['/usr/bin/.lib/0.13.1']
}

vcsrepo { 'vindinium-src':
  path     => '/var/www/vindinium',
  ensure   => present,
  provider => git,
  source   => "git://github.com/ornicar/vindinium.git",
  owner    => $::ssh_username,
  group    => $::ssh_username,
  require  => [ Package['scala'], Wget::Fetch['sbt-launch'] ],
  notify   => Exec['sbt compile']
}

package { 'openjdk-7-jdk':
  ensure => present
}

exec { 'sbt compile':
  cwd         => '/var/www/vindinium',
  timeout     => 10000,
  user        => $::ssh_username,
  group       => $::ssh_username,
  creates     => '/var/www/vindinium/target',
  refreshonly => false,
  require     => [ Package['openjdk-7-jdk'] ]
}

exec { 'sbt stage':
  cwd         => '/var/www/vindinium',
  timeout     => 10000,
  user        => $::ssh_username,
  group       => $::ssh_username,
  creates     => '/var/www/vindinium/target/universal',
  refreshonly => false,
  require     => Exec['sbt compile']
}

nginx::resource::vhost { "${www_domain}":
  listen_port          => 80,
  use_default_location => false
}

nginx::resource::location { "${www_domain}--root":
  vhost                => "${www_domain}",
  location             => '/',
  proxy                => 'http://127.0.0.1:9000/',
  proxy_read_timeout   => '24h',
  location_cfg_append  => {
    proxy_http_version => '1.1'
  }
}

file { 'vindinium-upstart':
  path    => '/etc/init/vindinium.conf',
  ensure  => 'file',
  owner   => 'root',
  group   => 'root',
  source  => '/vagrant/puppet/files/upstart/vindinium.conf',
  require => [ Exec['sbt stage'], Service['mongodb'], Nginx::Resource::Vhost["${www_domain}"] ]
}

service { 'vindinium':
  ensure     => running,
  enable     => true,
  hasstatus  => true,
  hasrestart => true,
  require    => File['vindinium-upstart']
}
