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
	  # cross platform pkgs
	  pkgsCross.mingwW64.buildPackages.gcc
	  # still buggy: pkgsCross.mingwW64.openalSoft
	  pkgsCross.mingwW64.gmp.static
	  pkg-config
        ];

        shellHook = ''
        '';
      };
    };
}


