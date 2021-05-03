FROM ubuntu:latest
RUN	apt-get update && \
	 apt-get install -y --no-install-recommends sudo \
	 libsdl2-2.0-0 \
	 libgl-dev \
	 libopengl0

COPY ./usr/tmp /usr/tmp
RUN chmod +x /usr/tmp/start.sh
CMD ["/usr/tmp/start.sh"]