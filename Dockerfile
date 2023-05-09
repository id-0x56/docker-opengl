FROM nvidia/opengl:1.2-glvnd-devel-ubuntu20.04

ENV DEBIAN_FRONTEND noninteractive

ARG USERNAME=ubuntu
ARG USER_UID=1000
ARG USER_GID=$USER_UID
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME

ENV TZ=Europe/London
RUN apt update \
    && apt install --no-install-recommends -y tzdata \
    && rm -rf /var/lib/apt/lists/* \
    && ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone

RUN apt update \
    && apt upgrade -y \
    && apt install --no-install-recommends -y build-essential cmake pkg-config gdb \
        libgtk-3-dev \
        libsdl2-dev \
        git curl mc \
        glmark2 \
    && rm -rf /var/lib/apt/lists/*

USER $USERNAME



# docker builder prune -af \
#     && docker system prune -af \
#     && docker volume prune -f \
#     && docker image prune -af



# docker login
# docker build --no-cache -t 00x56/docker-opengl:latest .
# docker push 00x56/docker-opengl:latest



# xhost +si:localuser:root
# xhost +local:
# docker run --rm --interactive --tty --gpus all --volume $(pwd)/app:/app --workdir /app --volume /tmp/.X11-unix:/tmp/.X11-unix --env DISPLAY=$DISPLAY 00x56/docker-opengl /bin/bash
# docker exec --interactive --tty --user root 7809913082a3 /bin/bash
# docker exec --interactive --tty 7809913082a3 /bin/bash
# xhost -local:
# xhost -

# __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia /app/build/opengl-app



# nvidia-smi -i 0 --query-gpu=uuid --format=csv

# xhost +si:localuser:root
# xhost +local:
# docker run --rm --interactive --tty --runtime=nvidia --gpus device=GPU-f3cc19f9-8084-1761-adff-ba2b42da49f9 --volume $(pwd)/app:/app --workdir /app --volume /tmp/.X11-unix:/tmp/.X11-unix --env DISPLAY=$DISPLAY 00x56/docker-opengl /bin/bash
# docker exec --interactive --tty --user root 7809913082a3 /bin/bash
# docker exec --interactive --tty 7809913082a3 /bin/bash
# xhost -local:
# xhost -

# __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia /app/build/opengl-app
