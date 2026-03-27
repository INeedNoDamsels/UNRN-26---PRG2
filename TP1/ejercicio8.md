# 8. El Autómata Unidimensional
### Variables internas
- `fila[10]`: Arreglo de tipo bool que representa el estado actual de la fila.  
  - `true` → celda ocupada (`#`).
  - `false` → celda libre (` `).
- `nueva[10]`: Arreglo auxiliar de tipo bool utilizado para calcular el siguiente estado de la fila.
- `i`: Índice para recorrer los arreglos. Es una variable de tipo int.

---

### Variables de salida (implícito)
- Salida por consola:
  - Representación de la fila de 10 celdas en cada iteración:
    - `#` → celda activa.
    - ` ` → celda inactiva.
- `return 0`: Indica la finalización correcta del programa.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `main()`
- El arreglo `fila[10]` debe poder inicializarse correctamente.
- El programa asume un tamaño fijo de fila (10 celdas).
- La fila inicial se genera aleatoriamente mediante `obtener()`.

---

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** La fila inicial se genera aleatoriamente con valores `true` o `false`.

**2.** Cada iteración del bucle infinito realiza:
   - Impresión de la fila actual en consola.
   - Pausa de 2 segundos mediante `lapso(2)`.
   - Cálculo del siguiente estado para las posiciones `1` a `8`:
     - `nueva[i] = (fila[i-1] == fila[i+1])`
   - Actualización del arreglo `fila` con los valores de `nueva`.

**3.** El programa se ejecuta de manera continua o hasta que se interrumpa externamente.

**4.** Todas las actualizaciones respetan la regla de vecindad definida, evitando así el "efecto dominó".