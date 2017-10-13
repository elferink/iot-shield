FROM alpine
RUN apk add --no-cache darkhttpd
ADD https://github.com/hivemq/hivemq-mqtt-web-client/archive/master.zip /www/
RUN unzip /www/master.zip -d /www
RUN echo "websocketserver = 'localhost'; \
websocketport = 9001;" > /www/hivemq-mqtt-web-client-master/config.js
RUN sed -i "s/\'clientId-\'/\'mqttdash-\'/" /www/hivemq-mqtt-web-client-master/index.html && \
	sed -i "s/<\/body>/<script>setTimeout(function(){websocketclient.connect()},200);<\/script><\/body>/" /www/hivemq-mqtt-web-client-master/index.html

CMD ["darkhttpd", "/www/hivemq-mqtt-web-client-master"]
EXPOSE 80
