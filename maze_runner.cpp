#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>

// Representação do labirinto
using Maze = std::vector<std::vector<char>>;

using namespace std;
// Estrutura para representar uma posição no labirinto
struct Position {
    int row;
    int col;
};

// Variáveis globais
Maze maze;
int num_rows;
int num_cols;
std::stack<Position> valid_positions;
// Função para carregar o labirinto de um arquivo 
Position load_maze(const std::string& file_name) {
    // TODO: Implemente esta função seguindo estes passos:
    // 1. Abra o arquivo especificado por file_name usando std::ifstream
    // 2. Leia o número de linhas e colunas do labirinto
    // 3. Redimensione a matriz 'maze' de acordo (use maze.resize())
    // 4. Leia o conteúdo do labirinto do arquivo, caractere por caractere
    // 5. Encontre e retorne a posição inicial ('e')
    // 6. Trate possíveis erros (arquivo não encontrado, formato inválido, etc.)
    // 7. Feche o arquivo após a leitura
    ifstream inFile(file_name); // 1. abrindo arquivo.
    if(!inFile){
        cout << "Erro ao abrir o arquivo do labirinto" << endl;
        exit(1);
    } 
    //int lin, col; 

    inFile >> num_rows >> num_cols; //2. lendo linhas e colunas.
    maze.resize(num_rows, vector<char>(num_cols));//3. redimensionando a matriz;

/*     for(int i = 0; i <= lin; i++){
        maze[i].resize(col);
    } */

    Position p_inicial = {-1, -1};
    for(int i = 0; i < num_rows; i++){ //4. Leia o conteudo do labirinto.
        for(int j = 0; j < num_cols; j++){
            inFile >> maze[i][j];

            if(maze[i][j] == 'e'){
                p_inicial.row = i; //numero da linha da posição inicial.
                p_inicial.col = j; //numero da coluna da posição inciiaç;
            }
        }
    }
    if(p_inicial.row == -1 || p_inicial.col == -1){ //6. tratamento de erro 1, fazer mais tratamentos...
        cout << "Erro: posição incial não encontrada." << endl;
        exit(1);
    }

    inFile.close(); // 7. fechar arquivo.
 // Placeholder - substitua pelo valor correto
    return p_inicial;
}
// Função para imprimir o labirinto
void print_maze() {
    // TODO: Implemente esta função
    // 1. Percorra a matriz 'maze' usando um loop aninhado
    // 2. Imprima cada caractere usando std::cout
    // 3. Adicione uma quebra de linha (std::cout << '\n') ao final de cada linha do labirinto
    for(int i = 0; i < num_rows; i++){ //1. Percorrendo a matriz. 
        for(int j = 0; j < num_cols; j++){
            cout << maze[i][j]; //Imprimindo cada caracter.
        }
        cout << '\n'; //3. Quebra de linha a cada linha. 
    }
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    // TODO: Implemente esta função
    // 1. Verifique se a posição está dentro dos limites do labirinto
    //    (row >= 0 && row < num_rows && col >= 0 && col < num_cols)
    // 2. Verifique se a posição é um caminho válido (maze[row][col] == 'x')
    // 3. Retorne true se ambas as condições forem verdadeiras, false caso contrário
    if((row >= 0) && (row < num_rows) && (col >= 0) && (col < num_cols)){ //1. Limites do labirinto.
        if((maze[row][col] == 'x')||(maze[row][col] == 's')){
            return true;
        } 
        return false; // Placeholder - substitua pela lógica correta
    }
    return false;  
}

// Função principal para navegar pelo labirinto
bool walk(Position pos) {
    // TODO: Implemente a lógica de navegação aqui
    // 1. Marque a posição atual como visitada (maze[pos.row][pos.col] = '.')
    // 2. Chame print_maze() para mostrar o estado atual do labirinto
    // 3. Adicione um pequeno atraso para visualização:
    //    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // 4. Verifique se a posição atual é a saída (maze[pos.row][pos.col] == 's')
    //    Se for, retorne true
    // 5. Verifique as posições adjacentes (cima, baixo, esquerda, direita)
    //    Para cada posição adjacente:
    //    a. Se for uma posição válida (use is_valid_position()), adicione-a à pilha valid_positions
    // 6. Enquanto houver posições válidas na pilha (!valid_positions.empty()):
    //    a. Remova a próxima posição da pilha (valid_positions.top() e valid_positions.pop())
    //    b. Chame walk recursivamente para esta posição
    //    c. Se walk retornar true, propague o retorno (retorne true)
    // 7. Se todas as posições foram exploradas sem encontrar a saída, retorne false
    //cout << "conteudo da prox. posição:  " << maze[pos.row][pos.col] << endl;
    if(maze[pos.row][pos.col] == 's'){ //4. verifique se é a saída.
        //cout << "entrei aqui."<< endl; 
        return true;
    }
    maze[pos.row][pos.col] = '.'; //1. Marcação posição atual.
    print_maze(); //2.; Atualização do labirinnto.
    this_thread::sleep_for(chrono::milliseconds(50)); //3. atraso
    Position pos_acima = {pos.row - 1, pos.col};
    Position pos_abaixo = {pos.row + 1, pos.col};
    Position pos_esquerda = {pos.row, pos.col - 1};
    Position pos_direita = {pos.row, pos.col + 1};
    if(is_valid_position(pos_acima.row, pos_acima.col)){
        valid_positions.push(pos_acima);
   }
    if(is_valid_position(pos_abaixo.row, pos_abaixo.col)){
        valid_positions.push(pos_abaixo);
   }
    if(is_valid_position(pos_esquerda.row, pos_esquerda.col)){
        valid_positions.push(pos_esquerda);
   }
    if(is_valid_position(pos_direita.row, pos_direita.col)){
        valid_positions.push(pos_direita);
   }
    while(!valid_positions.empty()){
        Position prox_pos = valid_positions.top();
        valid_positions.pop(); 
        if(walk(prox_pos)){ 
            return true;
        }
    }
  //  cout << "Cheguei aqui." << endl;
    return false; // Placeholder - substitua pela lógica correta
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_labirinto>" << std::endl;
        return 1;
    }

    Position initial_pos = load_maze(argv[1]);
    if (initial_pos.row == -1 || initial_pos.col == -1) {
        std::cerr << "Posição inicial não encontrada no labirinto." << std::endl;
        return 1;
    }

    bool exit_found = walk(initial_pos);
    //cout << "exit: " << exit_found << endl;
    if (exit_found) {
        std::cout << "Saída encontrada!" << std::endl;
    } else {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }

    return 0;
}

// Nota sobre o uso de std::this_thread::sleep_for:
// 
// A função std::this_thread::sleep_for é parte da biblioteca <thread> do C++11 e posteriores.
// Ela permite que você pause a execução do thread atual por um período especificado.
// 
// Para usar std::this_thread::sleep_for, você precisa:
// 1. Incluir as bibliotecas <thread> e <chrono>
// 2. Usar o namespace std::chrono para as unidades de tempo
// 
// Exemplo de uso:
// std::this_thread::sleep_for(std::chrono::milliseconds(50));
// 
// Isso pausará a execução por 50 milissegundos.
// 
// Você pode ajustar o tempo de pausa conforme necessário para uma melhor visualização
// do processo de exploração do labirinto.
