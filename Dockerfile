FROM anaderi/xfairsoft

RUN mkdir /tmp/FairRoot
COPY . /tmp/FairRoot
WORKDIR /tmp/FairRoot
RUN ./auto_build.sh cleanup
WORKDIR /root
