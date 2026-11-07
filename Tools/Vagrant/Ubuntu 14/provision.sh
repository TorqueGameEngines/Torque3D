# Make sure package listings are up to date.
apt-get update -y

# Install software for development.
sudo apt-get install \
	git \
	build-essential \
	nasm \
	cmake \
	cmake-qt-gui \
	pkg-config \
	ninja-build \
	gcc-multilib \
	g++-multilib \
	-y

# Install libraries.
sudo apt-get install \
	libogg-dev \
	libwayland-dev \
	libwayland-bin \
	wayland-protocols \
	libxkbcommon-dev \
	libdecor-0-dev \
	libegl1-mesa-dev \
	libopenal-dev \
	libfreetype6-dev \
	libfontconfig1-dev \
	libglu1-mesa-dev \
	-y
