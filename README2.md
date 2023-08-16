# Como compilar um extensão no Linux

- Instale o Pyenv, Git, Unzip e Wget.

- Utilize o Pyenv para instalar a última versão do Python 3.11 (enquanto fazia este tutorial, eu instalei o 3.11.4):

```
pyenv install 3.11.4
pyenv global 3.11.4
```

- Instale as dependências necessárias para compilar a biblioteca:

```
sudo apt update && sudo apt install clang lib32stdc++-7-dev lib32z1-dev libc6-dev-i386 g++-multilib
```

- No diretório home do usuário, crie a seguinte cadeia de diretórios:

```
mkdir -p ~/mods/source/sdk
```

- Entre no diretório `~/mods/source/sdk`, baixe os SDKs, descompacte e os renomeie:

```
wget https://github.com/alliedmodders/hl2sdk/archive/refs/heads/l4d.zip
unzip l4d.zip
rm l4d.zip
wget https://github.com/alliedmodders/sourcemod/archive/50b5bb197030ee05a82c9eef3358ebb81229c0e1.zip
unzip 50b5bb197030ee05a82c9eef3358ebb81229c0e1.zip
rm 50b5bb197030ee05a82c9eef3358ebb81229c0e1.zip
mv sourcemod-50b5bb197030ee05a82c9eef3358ebb81229c0e1 sourcemod-1.9.0.6245_zombieverse
wget https://github.com/alliedmodders/metamod-source/archive/198f723750a4091e7c9c86b8f56d1bf12fb41997.zip
unzip 198f723750a4091e7c9c86b8f56d1bf12fb41997.zip
mv metamod-source-198f723750a4091e7c9c86b8f56d1bf12fb41997 metamod-source-1.10.7-dev_zombieverse
rm 198f723750a4091e7c9c86b8f56d1bf12fb41997.zip
```

- Ainda dentro o diretório `~/mods/source/sdk`, baixe o SourceMod 1.7.2, pois precisaremos copiar alguns arquivos dele:

```
wget https://github.com/alliedmodders/sourcemod/archive/refs/tags/sourcemod-1.7.2.zip
unzip sourcemod-1.7.2.zip
rm sourcemod-1.7.2.zip
mv sourcemod-sourcemod-1.7.2 sourcemod-1.7.2
```

- Exporte as seguintes ENVs:

```
export HL2SDKL4D=/home/dartz/mods/source/sdk/hl2sdk-l4d
export SOURCEMOD=/home/dartz/mods/source/sdk/sourcemod-1.9.0.6245_zombieverse
export MMSOURCE=/home/dartz/mods/source/sdk/metamod-source-1.10.7-dev_zombieverse
```

- Instale o AMBuild:

```
cd ~/mods/source/sdk
git clone https://github.com/alliedmodders/ambuild
pip install ./ambuild
```

- Copie o diretório `public/sourcepawn` localizado no SourceMod 1.7.2 para dentro do SourceMod 1.9.0:

```
cp -r ~/mods/source/sdk/sourcemod-1.7.2/public/sourcepawn ~/mods/source/sdk/sourcemod-1.9.0.6245_zombieverse/public/
```

- Entre no diretório da extensão `sample_ext`:

```
cd ~/mods/source/sdk/sourcemod-1.9.0.6245_zombieverse/public/sample_ext
```

- Edite o arquivo `AMBuildScript` na linha 290 para que fique assim:

```
      os.path.join(self.sm_root, 'public', 'sourcepawn'),
```

- Ainda dentro do diretório da extensão, crie um diretório chamado `build` e entre nele:

```
mkdir build
cd build
```

- Execute o script `configure.py`:

```
python ../configure.py --sdks l4d
```

- Finalmente, execute o comando `ambuild`:

```
ambuild
```

- Se tudo correr bem, deverá ser exibida a seguinte mensagem ao final:

```
Build succeeded.
```

- Dentro do diretório `build` foram criados alguns subdiretórios, estando entre eles um diretório chamado `package`, que nada mais é que um diretório de distribuição:

```
$ ls -lha package/addons/sourcemod/extensions/
total 128K
drwxr-xr-x 2 dartz dartz 4.0K Aug 16 03:11 .
drwxr-xr-x 3 dartz dartz 4.0K Aug 16 02:55 ..
-rwxr-xr-x 1 dartz dartz 120K Aug 16 03:11 sample.ext.2.l4d.so
```

- Agora é só copiar a biblioteca em algum servidor Linux dedicado e testá-la.

- TODO: Testar a compilação sem as ENVs, simplesmente fornecendo as opções no script `configure.py`. Por exemplo:

```
python ../configure.py --sdks l4d --hl2sdk-root /home/dartz/mods/source/sdk --mms-path /home/dartz/mods/source/sdk/metamod-source-1.10.7-dev_zombieverse --sm-path /home/dartz/mods/source/sdk/sourcemod-1.9.0.6245_zombieverse
```

- Referências:
    - https://wiki.alliedmods.net/Building_SourceMod
    - https://www.youtube.com/watch?v=4eGLLbOumK8
