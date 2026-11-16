SIMULADOR DE PS4 - PORT INICIAL PARA NINTENDO WII

O QUE ESTA ENTREGO
- Projeto C++ nativo para Wii usando devkitPPC/libogc.
- Navegacao basica pelo Wii Remote.
- Tela inicial inspirada na organizacao do menu PS4.
- Tela Biblioteca demonstrativa.
- Makefile configurado para produzir ps4-simulator-wii.dol (renomeie para boot.dol para uso no Homebrew Channel).

LIMITACOES DESTA PRIMEIRA CONVERSAO
O HTML original usa DOM, CSS, Canvas, JavaScript, localStorage, selecao de arquivos e APIs exclusivas do Android.
Essas tecnologias nao existem no Wii. Por isso esta e uma reimplementacao inicial nativa, nao uma conversao automatica pixel a pixel.
A biblioteca ainda e demonstrativa: nao instala nem executa jogos Android. O Wii so pode executar homebrew/formatos compativeis.

COMO COMPILAR
1. Instale devkitPro com o grupo Wii (devkitPPC e libogc).
2. Abra um terminal na pasta deste projeto.
3. Execute: make
4. O arquivo .dol sera gerado na pasta do projeto. Copie-o para SD:/apps/ps4sim/boot.dol.
5. Crie tambem meta.xml e icon.png se quiser que o Homebrew Channel mostre nome e icone.

CONTROLES
- Direcional esquerdo/direito: mover selecao no menu principal.
- A: abrir item selecionado; abre Biblioteca quando selecionada.
- Direcional cima/baixo: navegar na Biblioteca.
- B: voltar.
- HOME: sair.

IMPORTANTE
Este ambiente nao possui a toolchain devkitPPC/libogc instalada, portanto o .dol nao foi compilado nem testado aqui.
