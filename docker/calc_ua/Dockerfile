FROM ubuntu:latest
RUN	apt-get update && \
	 apt-get install -y --no-install-recommends sudo \
	 qemu-system \
	 uml-utilities \
	 bridge-utils \
	 net-tools 

COPY ./usr/tmp /usr/tmp
RUN chmod +x /usr/tmp/start.sh
CMD ["/usr/tmp/start.sh"]