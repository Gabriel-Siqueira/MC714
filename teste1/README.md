nome: Gabriel Henriques Siqueira    ra: 155446

## MC714 - Teste 1

# Sequencial

Tempo para N = 64 e K = 2: 0m1.098s
Tempo para N = 64 e K = 4: 0m1.124s
Tempo para N = 64 e K = 8: 0m1.142s

# Multithread

        Na implementação utilizando multithread notamos que o tempo de execução
    é bem maior que na implementação sequencial. Também vemos que o aumento do
    numero de threads diminui o tempo de execução. 

Tempo para N = 64 e K = 2: 0m13.846s
Tempo para N = 64 e K = 4: 0m11.037s
Tempo para N = 64 e K = 8: 0m10.633s

# Multi-processo

        Na implementação utilizando multiplos processos notamos que o tempo de
    execução é menor que na implementação sequencial. Também vemos que o aumento do
    numero de processos diminui o tempo de execução. 

Tempo para N = 64 e K = 2: 0m0.948s
Tempo para N = 64 e K = 4: 0m0.834s
Tempo para N = 64 e K = 8: 0m0.829s
