{
  description = "nosering";

  inputs = {
    nixpkgs = { url = "github:NixOS/nixpkgs/nixpkgs-unstable"; };
    flake-utils = { url = "github:numtide/flake-utils"; };
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          nativeBuildInputs = with pkgs; [
            # order matters?: https://github.com/NixOS/nixpkgs/issues/76486
            clang-tools
            clang
          ];

          buildInputs = with pkgs; [
            catch2
          ];
        };
      }
    );
}
