FROM rockylinux:8
COPY xyce.rpm /tmp/xyce.rpm
RUN dnf install -y /tmp/xyce.rpm && dnf clean all
ENV PATH="/usr/local/XyceNF_7.10/bin:${PATH}"
ENTRYPOINT ["Xyce"]
