# Tarea 2 
Código base para tu tarea 2.

# Consideraraciones Importates para el Corrector

- Todos los tests funcionan.
- Los tests Lunatic obtuvieron menos de 5 segundos cada uno, probados con 1GB de RAM en WSL2.
- Hice pruebas en WSL2 y Ubuntu 18.04 (Máquina Virtual Hyper-V) y en WSL2..
- Para todas estas consideraciones, el programa fue ejecutado en un computador Intel Core i5 7200U con 16GB de memoria RAM, tanto en WSL2 como en Ubuntu 18.04 Hyper-V.

## Requerimientos
Debes tener instalada la librería `libpng` para poder leer las imágenes cómo matrices.  
Esta la puedes instalar con el comando:
```sudo apt install libpng-dev```

## Compilar y ejecutar
Compilar:
```make```

Ejecutar:
```./fumigate <input.txt>```

```./fumigate tests/queries/test0.txt```


