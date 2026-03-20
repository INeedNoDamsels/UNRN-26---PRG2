## 3. Control de Calidad
### Variables de entrada conceptuales (implícitas)
>Las entradas son los parámetros del sistema de generación y validación, no datos ingresados por teclado.
- `media = 15.0`: 
- `desviación estandar = 0.5`: 

### Constantes
- `MIN`: Indica el límite inferior de un rango. Es una variable de tipo float.
- `MAX`: Indica el límite superior de un rango. Es una variable de tipo float.
- `MEDIDAS`: Indica la cantidad de diámetros o medidas de una pieza fabricada. Es una variable de tipo int.
- `CANTIDAD`: Indica la cantidad de piezas fabricadas. Es una variable de tipo int.

### Variables internas
- `piezas[CANTIDAD][MEDIDAS]`: Es una matriz con los diámetros de cada pieza. Es un arreglo de arreglos de tipo float.
- `promedio`: Indica el promedio total del lote. Es una variable de tipo float.
- `desviacion`: Indica la diferencia entre una medida y el promedio. Es una variable de tipo float.

### Variables de salida
- `valido`: Indica si el lote analizado es aceptable o no. Es una variable booleana.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

- `MIN ∈ ℝ` y `MIN < MAX`
- `MAX ∈ ℝ` y `MAX > MIN`
- `CANTIDAD ∈ ℤ` y `CANTIDAD > 0`
- `MEDIDAS ∈ ℤ` y `MEDIDAS > 0`
- `desviacion ∈ ℝ` y `desviacion > 0`
- El sistema debe ser capaz de generar números aleatorios, entre un rango establecido por las variables `MIN` y `MAX` utilizando la función `random_device`.

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se habrá generado una matriz `piezas` de tamaño `CANTIDAD`×`MEDIDAS`.

**2.** El promedio calculado contendrá el valor de evaluar la suma de todas las medidas entre la cantidad de elementos de la matriz `piezas`.

**3.** La variable `valido` == `true` ⟺ (promedio ∈ [`MIN`, `MAX`]) ^ (∀ pieza, ∀ medida: desviacion ≤ 10% del promedio).

**4.** Se informará si el lote es o no aceptable.
- Si `valido = true`, se imprimirá “*aceptable*”.
- Si `valido = false`, se imprimirá “*no aceptable*”.

**5.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.