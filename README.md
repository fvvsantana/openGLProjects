## Requisitos para compilação:
* cmake
* make
* g++ com suporte a C++ 17
* assimp

### Instalando assimp:

Para instalar assimp no ubuntu 18.04 execute:
	sudo apt-get install libassimp4 assimp-utils

Para outras distribuições, instale a partir do código fonte:
```
	git clone https://github.com/assimp/assimp.git
	cd assimp
	mkdir build
	cd build
	cmake ..
	sudo make install
```

## Executando o projeto

Para executar o projeto siga as instruções:

Baixe o repositório.
Crie um arquivo 'scene.txt' na raiz do projeto com cada modelo a ser carregado na aplicação em uma linha.
Crie a pasta build na raiz do projeto:
```
    mkdir build && cd build
```

Prepare o ambiente:
```
    cmake ..
```

Compile e execute:
```
    make run
```
