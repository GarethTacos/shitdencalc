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
          clang
          valgrind
	  openal
	  opusfile
	  libogg
	  libopus
	  gmp
	  libtommath
	  emscripten
	  nodejs
	  yarn
	  python3
	  notcurses
	  mpfr
	  pkg-config
        ];

        shellHook = ''
        '';
      };
    };
}


