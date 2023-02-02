# https://developers.home-assistant.io/docs/add-ons/configuration#add-on-dockerfile
ARG BUILD_FROM
FROM $BUILD_FROM

RUN \
    #echo "@main http://dl-cdn.alpinelinux.org/alpine/last_stavle/main" >> /etc/apk/repositories && \
    #echo "@community http://dl-cdn.alpinelinux.org/alpine/v3.17/community" >> /etc/apk/repositories && \
    echo "@edge http://dl-cdn.alpinelinux.org/alpine/edge/community" >> /etc/apk/repositories

# Upgrade Alpine and base packages
RUN apk update --no-cache

RUN \
    apk add --no-cache \
    python3 \
    py3-pip \
    wiringpi-dev \
    g++ \
    gcc
#WORKDIR /data

RUN \
    pip install paho-mqtt

# Kompilacja ORNO
COPY ./compile/orno.cpp /
RUN echo "Kompilacja ORNO... " 
RUN g++ -o orno orno.cpp -lwiringPi

# Kompilacja MAKEGOOD
COPY ./compile/MAKEGOOD.cpp /
RUN echo "Kompilacja MAKEGOOD... " 
RUN g++ -o MAKEGOOD MAKEGOOD.cpp -lwiringPi

# Kompilacja ORNO_DIMMER
COPY ./compile/orno_dimmer.cpp /
RUN echo "Kompilacja ORNO_DIMMER... " 
RUN g++ -o orno_dimmer orno_dimmer.cpp -lwiringPi

# USUNIECIE ZBEDNYCH PAKIETOW
RUN echo "CZYSZCZENIE... " 
RUN rm orno.cpp MAKEGOOD.cpp orno_dimmer.cpp
RUN apk del g++ gcc --quiet

# Copy data for add-on
COPY main.py /
RUN chmod a+x /main.py
CMD ["python","-u","./main.py"]
