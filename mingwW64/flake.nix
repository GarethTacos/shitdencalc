{
  description = "Development environment with Clang and Valgrind";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }:
# old flake was lost so had to make new one
    let
      system = "x86_64-linux"; 
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShell.${system} = pkgs.mkShell {
        buildInputs = with pkgs; [
	pkgsCross.mingwW64.buildPackages.gcc
	pkgsCross.mingw32.buildPackages.gcc
	wget
	pkgsCross.mingwW64.buildPackages.cmake
	pkgsCross.mingwW64.buildPackages.gnumake
	pkgsCross.mingwW64.buildPackages.makedepend
	pkgsCross.mingwW64.libogg.dev
	pkgsCross.mingwW64.buildPackages.libpthread-stubs
	pkgsCross.mingwW64.libopus.dev
	pkgsCross.mingwW64.opusfile.dev
	#pkgsStatic.openal (have to build for windows manually most likely)...
	# gmp hates me
	pkgsCross.mingwW64.gmp.static.dev
	#gmp
	#mpfr
	#pkgsCross.mingwW64.buildPackages.opusfile.dev (bad does not have dlls)
	#pkgsCross.mingwW64.buildPackages.
	pkg-config
	libpulseaudio
	alsa-lib
	wineWow64Packages.full
	];

        shellHook = ''
   # so build process no die
    #export CC=x86_64-w64-mingw32-gcc
    #export CXX=x86_64-w64-mingw32-g++
        '';
      };
    };
}


