/*
 * PROBLEMA: Runner Pawns
 * Objetivo: Cavalo deve capturar todos os peões que avançam uma casa por turno
 * Estratégia: BFS (Busca em Largura) para encontrar o número mínimo de movimentos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes do problema
#define MAXP 8          // Máximo de peões no tabuleiro
#define MAXQ 2000000    // Tamanho máximo da fila para BFS
#define VISMAX 200003   // Tamanho da tabela hash para estados visitados

// Estrutura que representa um estado do jogo
typedef struct {
  int knight_position;      // Posição atual do cavalo (1-64)
  int number_of_pawns;      // Quantidade de peões ainda no tabuleiro
  int pawn_positions[MAXP]; // Array com as posições de todos os peões
  int distance_from_start;  // Número de movimentos desde o estado inicial
} State;

// Movimentos possíveis do cavalo no xadrez (L-shaped moves)
// Cada par representa (delta_linha, delta_coluna)
int KNIGHT_MOVES[8][2] = {
  {2,1}, {1,2}, {-1,2}, {-2,1},    // Movimentos para cima-direita
  {-2,-1}, {-1,-2}, {1,-2}, {2,-1} // Movimentos para baixo-esquerda
};

/*
 * FUNÇÕES DE CONVERSÃO DE COORDENADAS
 * O tabuleiro é numerado de 1 a 64:
 * 1-8 (primeira linha), 9-16 (segunda linha), ..., 57-64 (última linha)
 */

// Converte posição linear (1-64) para coordenadas (linha, coluna) base-0
void position_to_row_column(int position, int *row, int *column) {
  position--; // Converte para base-0
  *row = position / 8;    // Linha = posição dividida por 8
  *column = position % 8; // Coluna = resto da divisão por 8
}

// Converte coordenadas (linha, coluna) base-0 para posição linear (1-64)
int row_column_to_position(int row, int column) {
  return row * 8 + column + 1; // +1 para converter para base-1
}

/*
 * GERAÇÃO DE MOVIMENTOS DO CAVALO
 * Gera todos os movimentos válidos do cavalo a partir de uma posição
 * Retorna o número de movimentos possíveis
 */
int get_knight_moves_from_position(int position, int *output_moves) {
  int row, column;
  position_to_row_column(position, &row, &column);
  int move_count = 0;
  
  // Testa todos os 8 movimentos possíveis do cavalo
  for (int i = 0; i < 8; i++) {
    int new_row = row + KNIGHT_MOVES[i][0];
    int new_column = column + KNIGHT_MOVES[i][1];
    
    // Verifica se o movimento está dentro do tabuleiro (0-7)
    if (new_row >= 0 && new_row < 8 && new_column >= 0 && new_column < 8) {
      output_moves[move_count++] = row_column_to_position(new_row, new_column);
    }
  }
  
  return move_count; // Retorna quantos movimentos válidos foram encontrados
}

/*
 * ALGORITMO DE ORDENAÇÃO SIMPLES
 * Ordena um array de inteiros em ordem crescente
 * Usado para normalizar as posições dos peões (facilita comparação de estados)
 */
void sort_array(int *array, int size) {
  // Bubble sort simples - suficiente para arrays pequenos (≤ 8 elementos)
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (array[j] < array[i]) {
        // Troca os elementos de posição
        int temp = array[i]; 
        array[i] = array[j]; 
        array[j] = temp;
      }
    }
  }
}

/*
 * COMPARAÇÃO DE ESTADOS
 * Verifica se dois estados do jogo são idênticos
 * Necessário para evitar processar o mesmo estado múltiplas vezes
 */
int equal_state(State *a, State *b) {
  // Primeiro verifica se cavalo e número de peões são iguais
  if (a->knight_position != b->knight_position || a->number_of_pawns != b->number_of_pawns) 
    return 0;
  
  // Depois verifica se todas as posições dos peões são iguais
  // (arrays já estão ordenados, então comparação direta funciona)
  for (int i = 0; i < a->number_of_pawns; i++) {
    if (a->pawn_positions[i] != b->pawn_positions[i]) 
      return 0;
  }
  
  return 1; // Estados são idênticos
}

/*
 * SISTEMA DE HASH PARA CONTROLE DE ESTADOS VISITADOS
 * Evita processar o mesmo estado múltiplas vezes durante a busca
 * Usa hash table com linear probing para resolver colisões
 */

State visited_states[VISMAX];        // Tabela que armazena os estados visitados
int visited_slots_used[VISMAX];      // Controla quais posições da tabela estão ocupadas

// Calcula o hash de um estado baseado na posição do cavalo e dos peões
int calculate_state_hash(State *state) {
  long long hash_value = state->knight_position;
  
  // Combina posição do cavalo com posições de todos os peões
  for (int i = 0; i < state->number_of_pawns; i++) {
    hash_value = hash_value * 131LL + state->pawn_positions[i];
  }
  
  // Garante que o hash seja positivo
  if (hash_value < 0) hash_value = -hash_value;
  
  return (int)(hash_value % VISMAX); // Mapeia para o range da tabela
}

// Verifica se um estado já foi visitado anteriormente
int is_state_visited(State *state) {
  int hash_index = calculate_state_hash(state);
  int start_index = hash_index;
  
  // Linear probing: procura por uma posição livre ou pelo estado
  while (visited_slots_used[hash_index]) {
    // Se encontrou o estado, já foi visitado
    if (equal_state(&visited_states[hash_index], state)) return 1;
    
    // Próxima posição (circular)
    hash_index = (hash_index + 1) % VISMAX;
    
    // Se voltou ao início, a tabela está cheia (não deveria acontecer)
    if (hash_index == start_index) break;
  }
  
  return 0; // Estado não foi visitado
}

// Marca um estado como visitado na tabela hash
void mark_state_as_visited(State *state) {
  int hash_index = calculate_state_hash(state);
  
  // Linear probing: procura primeira posição livre
  while (visited_slots_used[hash_index]) {
    hash_index = (hash_index + 1) % VISMAX;
  }
  
  // Marca a posição como ocupada e armazena o estado
  visited_slots_used[hash_index] = 1;
  visited_states[hash_index] = *state;
}

/*
 * ALGORITMO PRINCIPAL - BFS (Busca em Largura)
 * Encontra o número mínimo de movimentos para capturar todos os peões
 * Retorna -1 se for impossível
 */
int solve_instance(int number_of_pawns, int *pawn_positions, int knight_start_position) {
  // Cria o estado inicial do jogo
  State start;
  start.knight_position = knight_start_position;
  start.number_of_pawns = number_of_pawns;
  
  // Copia as posições dos peões e ordena para normalização
  for (int i = 0; i < number_of_pawns; i++) {
    start.pawn_positions[i] = pawn_positions[i];
  }
  sort_array(start.pawn_positions, start.number_of_pawns);
  start.distance_from_start = 0; // Distância inicial é zero

  // Inicializa a fila para BFS
  static State queue[MAXQ];
  int queue_head = 0, queue_tail = 0;
  queue[queue_tail++] = start; // Adiciona estado inicial à fila

  // Limpa a tabela de estados visitados (importante para múltiplos test cases)
  memset(visited_slots_used, 0, sizeof(visited_slots_used));
  mark_state_as_visited(&start); // Marca estado inicial como visitado

  // Posições da última linha do tabuleiro (onde peões se tornam "reis")
  const int last_row_start = 57, last_row_end = 64;

  // Loop principal do BFS - processa estados enquanto houver itens na fila
  while (queue_head < queue_tail) {
    State current_state = queue[queue_head++]; // Remove estado da frente da fila

    // CONDIÇÃO DE VITÓRIA: se não há mais peões, o jogo foi vencido
    if (current_state.number_of_pawns == 0) {
      return current_state.distance_from_start;
    }

    // Conta quantos "reis" (peões na última linha) existem no estado atual
    // REGRA: se houver 2+ reis, o cavalo não pode capturar todos em um turno
    int kings_count_now = 0, king_position = -1;
    for (int i = 0; i < current_state.number_of_pawns; i++) {
      if (current_state.pawn_positions[i] >= last_row_start && 
          current_state.pawn_positions[i] <= last_row_end) {
        kings_count_now++;
        king_position = current_state.pawn_positions[i];
      }
    }
    
    // Se há 2+ reis, este ramo é inválido (cavalo só pode mover uma vez por turno)
    if (kings_count_now >= 2) continue;

    // Gera todos os movimentos possíveis do cavalo
    int possible_moves[8];
    int number_of_moves = get_knight_moves_from_position(current_state.knight_position, possible_moves);

    // REGRA ESPECIAL: se há exatamente um rei, o cavalo DEVE capturá-lo neste turno
    // (senão o rei permanecerá na última linha para sempre)
    if (kings_count_now == 1) {
      int can_capture = 0;
      // Verifica se o cavalo pode mover para a posição do rei
      for (int i = 0; i < number_of_moves; i++) {
        if (possible_moves[i] == king_position) { 
          can_capture = 1; 
          break; 
        }
      }
      
      // Se não pode capturar o rei, este ramo é inválido
      if (!can_capture) continue;
      
      // Força o movimento para capturar o rei
      possible_moves[0] = king_position;
      number_of_moves = 1;
    }

    // Testa cada movimento possível do cavalo
    for (int i = 0; i < number_of_moves; i++) {
      int next_knight_position = possible_moves[i];
      int new_pawn_positions[MAXP], new_number_of_pawns = 0;

      // CAPTURA: remove o peão se o cavalo aterrissar na mesma casa
      for (int j = 0; j < current_state.number_of_pawns; j++) {
        if (current_state.pawn_positions[j] != next_knight_position) {
          new_pawn_positions[new_number_of_pawns++] = current_state.pawn_positions[j];
        }
      }

      // VERIFICAÇÃO DE SOBREVIVÊNCIA: cavalo morre se um peão puder capturá-lo
      // (peão captura diagonalmente, então posição_peão + 8 == posição_cavalo)
      int knight_will_be_captured = 0;
      for (int j = 0; j < new_number_of_pawns; j++) {
        if (new_pawn_positions[j] + 8 == next_knight_position) { 
          knight_will_be_captured = 1; 
          break; 
        }
      }
      if (knight_will_be_captured) continue; // Cavalo morreria, movimento inválido

      // AVANÇO DOS PEÕES: todos os peões sobreviventes avançam uma casa (+8)
      for (int j = 0; j < new_number_of_pawns; j++) {
        new_pawn_positions[j] += 8;
      }

      // VERIFICAÇÃO DE REIS MÚLTIPLOS: se 2+ peões viraram reis, estado inválido
      int kings_count_after = 0;
      for (int j = 0; j < new_number_of_pawns; j++) {
        if (new_pawn_positions[j] >= last_row_start && 
            new_pawn_positions[j] <= last_row_end) {
          kings_count_after++;
        }
      }
      if (kings_count_after >= 2) continue; // Estado inválido

      // CRIA NOVO ESTADO para adicionar à fila
      State next_state;
      next_state.knight_position = next_knight_position;
      next_state.number_of_pawns = new_number_of_pawns;
      next_state.distance_from_start = current_state.distance_from_start + 1;
      
      // Copia posições dos peões e ordena para normalização
      for (int j = 0; j < new_number_of_pawns; j++) {
        next_state.pawn_positions[j] = new_pawn_positions[j];
      }
      sort_array(next_state.pawn_positions, next_state.number_of_pawns);

      // Se este estado nunca foi visitado, adiciona à fila para processamento
      if (!is_state_visited(&next_state)) {
        mark_state_as_visited(&next_state);
        if (queue_tail < MAXQ) {
          queue[queue_tail++] = next_state;
        }
      }
    }
  }

  return -1; // Não foi possível capturar todos os peões
}

/*
 * FUNÇÃO PRINCIPAL
 * Lê múltiplos test cases e resolve cada um independentemente
 */
int main() {
  int number_of_pawns;
  
  // Lê test cases até encontrar 0 (fim da entrada)
  while (scanf("%d", &number_of_pawns) == 1) {
    if (number_of_pawns == 0) break; // Condição de parada
    
    // Lê as posições iniciais dos peões
    int pawn_positions[MAXP];
    for (int i = 0; i < number_of_pawns; i++) {
      scanf("%d", &pawn_positions[i]);
    }
    
    // Lê a posição inicial do cavalo
    int knight_start_position; 
    scanf("%d", &knight_start_position);
    
    // Resolve o problema e imprime o resultado
    int answer = solve_instance(number_of_pawns, pawn_positions, knight_start_position);
    if (answer == -1) {
      printf("impossible\n"); // Não há solução
    } else {
      printf("%d\n", answer); // Número mínimo de movimentos
    }
  }
  
  return 0;
}
