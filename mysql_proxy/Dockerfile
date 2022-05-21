# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run:
#   docker build -t clion/remote-c-env-centos:1.1 -f Dockerfile .
#   docker run -d --cap-add sys_ptrace -p127.0.0.1:2232:22 -p127.0.0.1:8080:8080 --name clion_remote_env_centos clion/remote-c-env-centos:1.1
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[localhost]:2232"
#   ssh-keygen -f "$HOME/.ssh/known_hosts" -R "[127.0.0.1]:2232"
#
# stop:
#   docker stop clion_remote_env
# 
# ssh credentials (test user):
#   user@password 

FROM centos:7


RUN yum -y update \
 && yum -y install openssh-server \
  make \
  build-essential \
  gcc \
  gcc-c++ \
  gdb \
  clang \
  cmake \
  rsync \
  tar \
  python \
 && yum clean all


RUN ssh-keygen -A

RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/libexec/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_test_clion

RUN localedef -i en_US -f UTF-8 en_US.UTF-8

RUN useradd -m user \
  && yes password | passwd user

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test_clion"]