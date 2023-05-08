# MULTIMIDIA

## CODIGO DE HUFFMAN

O código de Huffman é uma codificação do tipo VLC (Variable Length Coding). O objetivo é codificar os símbolos de uma mensagem de acordo com a frequência de ocorrência de cada um deles. A codificação é inversamente proporcional à probabilidade de ocorrência e geralmente é binária. Uma explicação detalhada pode ser encontrada em [huffman IME-USP](https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/huffman.html).

O algoritmo que gera a árvore binária do código de Huffman segue os seguintes passos

1. Inicializar os nós que representam cada símbolo com o valor que o representa e sua frequência
2. Encontrar os dois nós com menor frequência
3. Criar um nó intermadiário cujos filhos são os dois nós citados no passo 2 e cuja frequência é a soma dos dois filhos
4. Caso haja mais de um nó restante, repetir passos 2 e 3


## BUILD

Antes de mais nada, o projeto não necessita de dependências externas. 

O projeto pode ser compilado usando cmake. Para isso, navegue até a pasta build e rode **cmake ..**. Esse comando vai gerar os arquivos necessários para o build system padrão de acordo com o sistema operacional. Em um MAC ou máquina Linux, por exemplo, será gerado um makefile. O build system específico pode ser fornecido como parâmetro na chamada do cmake. Caso isso seja desejado, pode-se consultar a [documentação de referência do cmake](https://cmake.org/cmake/help/latest/).
