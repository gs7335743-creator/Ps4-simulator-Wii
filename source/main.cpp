#include <gccore.h>
#include <wiiuse/wpad.h>
#include <ogc/system.h>
#include <ogc/video.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

static GXRModeObj *rmode;
static void *xfb = nullptr;
static std::vector<std::string> tiles = {
    "PlayStation Store", "What's New", "Jogos", "TV e vídeo",
    "Biblioteca", "PlayStation Now", "Galeria", "Música", "Configurações"
};
static int selected = 1;
static bool inLibrary = false;
static int libraryIndex = 0;
static const char *games[] = {"Minecraft", "Roblox", "Free Fire", "Terraria", "Adicionar jogo"};

static void initVideo() {
    VIDEO_Init();
    rmode = VIDEO_GetPreferredMode(nullptr);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight,
                 rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

static void drawHome() {
    printf("\x1b[2J");
    printf("\x1b[1;36m\n\n                    SIMULADOR DE PS4 - NINTENDO WII\x1b[0m\n");
    printf("\x1b[0;37m\n      Amigos                         Perfil: Jogador                  Trofeus: 2\n\n\n");
    for (size_t i = 0; i < tiles.size(); ++i) {
        if ((int)i == selected) printf("   \x1b[1;37;44m  [ %-22s ]  \x1b[0m\n", tiles[i].c_str());
        else                    printf("   \x1b[0;37;44m    %-22s    \x1b[0m\n", tiles[i].c_str());
    }
    printf("\n\x1b[1;37m   %s\x1b[0m\n", tiles[selected].c_str());
    printf("\x1b[0;90m\n   Wii Remote: esquerda/direita para navegar | A abrir | B voltar\n");
    printf("   Home para sair\x1b[0m\n");
}

static void drawLibrary() {
    printf("\x1b[2J\x1b[1;36m\n\n                         BIBLIOTECA\x1b[0m\n\n");
    for (int i = 0; i < 5; ++i) {
        if (i == libraryIndex) printf("   \x1b[1;37;44m  > %-28s  \x1b[0m\n", games[i]);
        else printf("   \x1b[0;37;44m    %-28s  \x1b[0m\n", games[i]);
    }
    printf("\n\x1b[0;90m   A selecionar | B voltar | Cima/baixo navegar\x1b[0m\n");
    if (libraryIndex == 4) printf("\n   Esta versao inicial ainda nao instala jogos; a biblioteca e demonstrativa.\n");
}

int main(int argc, char **argv) {
    initVideo();
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    while (true) {
        WPAD_ScanPads();
        u32 down = WPAD_ButtonsDown(0);
        if (down & WPAD_BUTTON_HOME) break;
        if (inLibrary) {
            if (down & WPAD_BUTTON_B) inLibrary = false;
            if (down & WPAD_BUTTON_UP) { if (libraryIndex > 0) --libraryIndex; }
            if (down & WPAD_BUTTON_DOWN) { if (libraryIndex < 4) ++libraryIndex; }
            if (down & WPAD_BUTTON_A) {
                if (libraryIndex == 4) { /* reservado para futura tela de adicionar */ }
                else { /* Wii homebrew nao inicia apps Android */ }
            }
            drawLibrary();
        } else {
            if ((down & WPAD_BUTTON_LEFT) && selected > 0) --selected;
            if ((down & WPAD_BUTTON_RIGHT) && selected < (int)tiles.size() - 1) ++selected;
            if (down & WPAD_BUTTON_A) {
                if (selected == 4) { inLibrary = true; libraryIndex = 0; }
            }
            drawHome();
        }
        VIDEO_WaitVSync();
    }
    printf("\x1b[2J\n\n  Encerrando simulador...\n");
    VIDEO_WaitVSync();
    return 0;
}
