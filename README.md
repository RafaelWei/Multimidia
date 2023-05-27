# MULTIMÍDIA

## CODIGO DE HUFFMAN

O código de Huffman é uma codificação do tipo VLC (Variable Length Coding). O objetivo é codificar os símbolos de uma mensagem de acordo com a frequência de ocorrência de cada um deles. O comprimento dos códigos (geralmente binários) são inversamente proporcionais à frequência do símbolo que representam. Uma explicação detalhada pode ser encontrada [no material do IME-USP](https://www.ime.usp.br/~pf/estruturas-de-dados/aulas/huffman.html). Basicamente, é gerada uma árvore em que as folhas representam os símbolos e a codificação de cada um deles é feita caminhando da raiz até a respectiva folha da seguinte forma: o deslocamento do pai para o filho esquerdo adiciona um bit 0 e o deslocamento do pai para o filho direito adiciona um bit 1 à codificação.

O algoritmo que gera a árvore binária do código de Huffman segue os seguintes passos

1. Inicializar os nós que representam cada símbolo com o valor que o representa e sua frequência
2. Encontrar os dois nós com menor frequência
3. Criar um nó intermadiário cujos filhos são os dois nós citados no passo 2 e cuja frequência é a soma dos dois filhos
4. Caso haja mais de um nó restante, repetir passos 2 e 3

No caso deste projeto, o objetivo é codificar os valores dos pixels de uma imagem .pgm usando a codificação de Huffman. As imagens a seremcodificadas estão no diretório /res. 

## BUILD

**O projeto não necessita de dependências externas.**

O projeto pode ser compilado usando cmake. Para isso, navegue até a pasta build e rode **cmake ..** . Esse comando vai gerar os arquivos necessários para o build system padrão de acordo com o sistema operacional. Em um MAC ou máquina Linux, por exemplo, será gerado um makefile. O build system específico pode ser fornecido como parâmetro na chamada do cmake. Caso isso seja desejado, pode-se consultar a [documentação de referência do cmake](https://cmake.org/cmake/help/latest/).

## USAGE

Depois da compilação, serão gerados três executáveis: Encoder, Decoder e MSE. Eles devem ser executados nessa ordem, pois os executáveis cada um depende dos arquivos gerados pelos anteriores.
