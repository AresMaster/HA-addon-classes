# https://developers.home-assistant.io/docs/add-ons/configuration#add-on-dockerfile
ARG BUILD_FROM
FROM $BUILD_FROM

#RUN \
    #echo "@main http://dl-cdn.alpinelinux.org/alpine/v3.17/main" >> /etc/apk/repositories && \
    #echo "@community http://dl-cdn.alpinelinux.org/alpine/v3.17/community" >> /etc/apk/repositories && \
    #echo "@edge http://dl-cdn.alpinelinux.org/alpine/edge/main" >> /etc/apk/repositories

# Upgrade Alpine and base packages
#RUN apk update --no-cache

RUN \
    apk add --no-cache \
    python3 \
    py3-pip
#    wiringpi-dev \
#    g++ \
#    gcc
#WORKDIR /data

RUN \
    pip install paho-mqtt

#COPY orno.cpp /
#RUN g++ -o orno orno.cpp
# Copy data for add-on
COPY main.py /
RUN chmod a+x /main.py
CMD ["python", "./main.py"]
