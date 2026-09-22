// Ola, criei um aplicativo em C++	que funciona como um copiador de texto, simples 
// primeiro você coloca uma palavra e após isso, ele repete essa palavra e guarda dentro de uma lista inteira e apos
// printar ele simplesmente copia para a area de transferencia.
// Feito por mim(Isllan).

// O codigo da parte de transferencia, não foi feito por mim, foi feito por IA, mas o resto da logica, EU!

#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

// Lista
std::vector<std::string> listaaa;

// Codigo de referencia(Parte da area de transferencia)
// Função que copia uma string para o clipboard
bool CopiarParaClipboard(const std::string& texto) {
    // Abre o clipboard associando-o à janela atual
    if (!OpenClipboard(nullptr)) {
        return false;
    }

    // Limpa o clipboard de conteúdos anteriores
    EmptyClipboard();

    // Aloca memória global para o texto (+1 para o caractere nulo '\0')
    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, texto.size() + 1);
    if (!hGlob) {
        CloseClipboard();
        return false;
    }

    // Bloqueia a memória para permitir a cópia dos dados
    memcpy(GlobalLock(hGlob), texto.c_str(), texto.size() + 1);
    GlobalUnlock(hGlob);

    // Envia os dados no formato de texto padrão (CF_TEXT)
    if (!SetClipboardData(CF_TEXT, hGlob)) {
        GlobalFree(hGlob);
        CloseClipboard();
        return false;
    }

    // Fecha o clipboard para liberar o recurso para outros programas
    CloseClipboard();
    return true;
}

// okay, agora tenho que criar o copiador e que vai criar a lista de palavras, vou usar lista permanente, caso encerrar a sessão, perdera a lista
void adicionar_lista(const std::string& palavra, const int& limite) {
    // Não tera verificaçao, vamos ao direto e basico
    for (auto c = 0; c < limite; c++) {
        /// sempre uso std::flush é otimo, o texto aparece na hora
        listaaa.push_back(palavra);
    }
}

// Easy, com a IA meus manos, tudo fica mais facil, isso é fato, mAS NÃO ESQUECE A LOGICAAAAAAA

// Programa principal
int main() {
    int escolhas, escolher;
    std::string palavra;
    int maximo;
    std::string sim_nao;

    while (true) {
       
        std::cout << "Ola, voce deseja limpar a area de transferencia?\n" << std::flush;
        std::cout << "Sim para limpar e Nao para continuar\n" << std::flush;

        std::cin >> sim_nao;
        if (sim_nao.empty() == true) {
            std::cout << "Por favor digite algo\n" << std::flush;
        }
        else if (sim_nao == "Sim") {
            // --> CODIGO GERADO POR IA E ADAPTADO PARA O CODIGO ATUAL

             // 1. Tenta abrir a área de transferência vinculando-a à janela atual (NULL)
            if (OpenClipboard(NULL)) {

                // 2. Esvazia a área de transferência
                if (EmptyClipboard()) {
                    std::cout << "Area de transferencia limpa com sucesso!" << std::endl;
                }
                else {
                    std::cout << "Erro ao limpar a area de transferencia." << std::endl;
                }

                // 3. Sempre feche a área de transferência após abrir
                CloseClipboard();

            }
            else {
                std::cout << "Erro ao abrir a area de transferencia (pode estar sendo usada por outro app)." << std::endl;
            }
        }

        std::cout << "Ola, usuario, para sair, digite 1, para entrar, digite qualquer numero.\n" << std::flush;
        std::cin >> escolhas;

        if (escolhas == 1) {
            break;
            // Isso encerra a sessão e fecha tudo, guia e tudo
        }
        else {
            // agora sim

            std::cin.ignore(10000, '\n');

            std::cout << "Digite uma frase ou  palavra para ser copiada\n" << std::flush;
            std::getline(std::cin, palavra);

            std::cout << "Digite o limite maximo de repeticoes\n" << std::flush;
            std::cin >> maximo;

            adicionar_lista(palavra, maximo);

            std::cout << "Voce deseja adicionar mais ou acionar o motor logo?(1 e 2, 2 para motor e 1 para add)\n" << std::flush;
            std::cin >> escolher;

            std::cin.ignore(10000, '\n');
            if (escolher == 1) {
                std::cout << "Isso faz voce voltar do comeco,,,,\n" << std::flush;
                continue;
            }
            else if (escolher == 2) {
                std::string palavraCOMPLETA = "";

                for (auto p = 0; p < listaaa.size(); p++) {
                    palavraCOMPLETA += listaaa[p] + "\r\n";
                }

                if (CopiarParaClipboard(palavraCOMPLETA)) {
                    std::cout << "Lista copiada com sucesso!\n" << std::flush;
                }
                else {
                    std::cout << "Nao foi possivel copiar a lista de p.l\n" << std::flush;
                }
            }


        }
       
    }

    return 0;
}