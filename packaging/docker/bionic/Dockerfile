FROM ubuntu:bionic

LABEL description="Ubuntu Bionic ICL Build Environment"
ENV USER=user USER_ID=1000 USER_GID=1000

RUN apt-get update
RUN apt-get upgrade -y

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential git cmake python-pip dirmngr \
                       devscripts equivs apt-file debhelper sudo wget \
                       libjpeg-dev libpng-dev clang ca-certificates tzdata

ADD https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB /root/
RUN apt-key add /root/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB
RUN sh -c 'echo deb https://apt.repos.intel.com/mkl all main > /etc/apt/sources.list.d/intel-mkl.list'
RUN sh -c 'echo deb https://apt.repos.intel.com/ipp all main > /etc/apt/sources.list.d/intel-ipp.list'

RUN apt-get update
RUN apt-get install -y intel-mkl-2018.3-051 intel-ipp-2018.3-051
RUN apt-get clean

RUN groupadd --gid ${USER_GID} ${USER}
RUN useradd --uid ${USER_ID} --gid ${USER_GID} --create-home --shell /bin/bash ${USER}

WORKDIR /home/user
CMD ["workspace/packaging/scripts/docker-bootstrap.sh"]
