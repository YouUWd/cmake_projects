FROM ubuntu

# SET ENV DEBIAN_FRONTEND noninteractive  avoid of below!
# Please select the geographic area in which you live. Subsequent configuration questions will narrow this down by presenting a list of cities, representing
# the time zones in which they are located.
#
# 1. Africa   3. Antarctica  5. Arctic  7. Atlantic  9. Indian    11. SystemV  13. Etc
# 2. America  4. Australia   6. Asia    8. Europe    10. Pacific  12. US

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update \
  && apt-get install -y ssh \
    openssh-server \
    build-essential \
    gcc \
    g++ \
    gdb \
    cmake \
    rsync \
    tar \
    python \
    netcat-traditional \
  && apt-get clean
RUN useradd -m user && yes password | passwd user

# 赋予sudo权限并允许无密码sudo
RUN echo 'user ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

RUN mkdir -p /run/sshd
CMD ["/usr/sbin/sshd", "-D"]

USER ${USER}
RUN mkdir -p /home/user/