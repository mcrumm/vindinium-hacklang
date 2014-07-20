# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "puphpet/ubuntu1404-x64"
  config.vm.network "forwarded_port", guest: 80, host: 9000
  #config.vm.synced_folder "../data", "/vagrant_data"

  config.vm.provider "virtualbox" do |vb|
    host = RbConfig::CONFIG['host_os']

    # Give VM 1/4 system memory & access to all cpu cores on the host
    # @see http://www.stefanwrobel.com/how-to-make-vagrant-performance-not-suck
    if host =~ /darwin/
      cpus = `sysctl -n hw.ncpu`.to_i
      # sysctl returns Bytes and we need to convert to MB
      mem = `sysctl -n hw.memsize`.to_i / 1024 / 1024 / 4
    elsif host =~ /linux/
      cpus = `nproc`.to_i
      # meminfo shows KB and we need to convert to MB
      mem = `grep 'MemTotal' /proc/meminfo | sed -e 's/MemTotal://' -e 's/ kB//'`.to_i / 1024 / 4
    else # sorry Windows folks, I can't help you
      cpus = 2
      mem = 1024
    end

    vb.customize ["modifyvm", :id, "--memory", mem]
    vb.customize ["modifyvm", :id, "--cpus", cpus] 
  end

  config.vm.provision :shell do |s|
    s.path = "puppet/shell/execute-files.sh"
    s.args = ["exec-once", "exec-always"]
  end
  config.vm.provision :shell, run: "always" do |s|
    s.path = "puppet/shell/execute-files.sh"
    s.args = ["startup-once", "startup-always"]
  end

  if Vagrant.has_plugin?('vagrant-librarian-puppet')
    config.librarian_puppet.puppetfile_dir        = 'puppet'
    config.librarian_puppet.placeholder_filename  = '.gitignore'
  end

  config.vm.provision 'puppet' do |puppet|
    puppet.manifests_path     = 'puppet'
    puppet.module_path        = 'puppet/modules'
    puppet.hiera_config_path  = 'puppet/config.yaml'
    puppet.options            = [ '--verbose', '--debug' ]
  end

  config.ssh.forward_agent = true
end
