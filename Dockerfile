FROM debian:jessie

MAINTAINER Michael Crumm <mike@crumm.net>

RUN apt-key adv --recv-keys --keyserver hkp://keyserver.ubuntu.com:80 0x5a16e7281be7a449
RUN echo 'deb http://dl.hhvm.com/debian jessie main' > /etc/apt/sources.list.d/hhvm.list

RUN DEBIAN_FRONTEND=noninteractive apt-get update -q && \
    apt-get install -qy --no-install-recommends \
      hhvm \
      wget && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

COPY etc/custom.ini /etc/hhvm/custom.ini

RUN wget -q http://getcomposer.org/composer.phar && \
    mv composer.phar /usr/local/bin/composer && \
    chmod +x /usr/local/bin/composer

COPY etc/.bash_aliases /root/.bash_aliases
RUN cat ~/.bash_aliases >> ~/.bashrc && \
    rm ~/.bash_aliases

VOLUME /opt/hackdinium

ENV PATH $PATH:/opt/hackdinium/bin
