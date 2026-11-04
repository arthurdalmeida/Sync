# Sincronização do metrô

Implementação 4 de SO. Cada carro e cada passageiro é uma thread e as funções de sync_car.c organizam o embarque usando um mutex e duas variáveis de condição.

## Arquivos

- sync_car.h: contém a struct station e as assinaturas das funções.
- sync_car.c: contém station_init, station_wait_for_car, station_on_board e station_load_car.
- sync_car-runner.c: contém o teste e a main.
- Makefile: compila e limpa o projeto.

## Como usar

Compilar:

```bash
make
```

Rodar o teste:

```bash
./sync_car
```

Limpar:

```bash
make clean
```

## Sistema

Feito e testado no Ubuntu (WSL), deve funcionar em Linux e macOS.