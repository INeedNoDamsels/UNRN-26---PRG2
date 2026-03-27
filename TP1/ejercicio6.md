# 6. Sensor de Estabilidad
### Variables de entrada
- `lista[VALORES]`: Arreglo de tipo float con valores aleatorios generados por el sensor.
- `longitud`: Cantidad de elementos en un arreglo. Es una variable de tipo int.
- `arreglo`: Puntero a arreglo de tipo float que contiene valores de presión.
- `salida`: Puntero a arreglo de tipo float donde se almacenan valores filtrados.

---

### Variables internas
- `nuevo[VALORES]`: Arreglo de tipo float que contiene solo valores válidos (>= 0).
- `VALORES`: Constante de tipo int que indica la cantidad de valores generados por el sensor.
- `i`, `j`: Índices para recorrer arreglos. Son variables de tipo int.
- `promedio`: Variable de tipo float para almacenar el promedio calculado de los valores válidos.

---

### Variables de salida (implícito)
- Salida por consola:
  - Lista original de valores detectados por el sensor.
  - Cantidad de elementos eliminados por ser inválidos.
  - Promedio de valores válidos.
- `return 0`: Indica la finalización correcta del programa.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `redondear()`
- `valor ∈ ℝ`

#### En `limpiar()`
- `longitud >= 0`.

#### En `promediar()`
- `arreglo` debe contener `longitud` elementos válidos.
- `longitud >= 0`.

#### En `main()`
- Los valores aleatorios generados por el sensor deben estar dentro del rango `[-9.99, 45.0]`.

---

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se generarán 15 valores aleatorios representando lecturas del sensor.

**2.** Cada valor se redondea a dos decimales mediante `redondear()`.

**3.** Se filtran los valores negativos con `limpiar()`:
   - Los valores >= 0 se copian a `nuevo`.
   - Se devuelve la cantidad de elementos válidos.

**4.** Se imprime en consola:
   - Lista original de valores detectados.
   - Cantidad de elementos eliminados.

**5.** Si existen valores válidos:
   - Se calcula el promedio con `promediar()`.
   - Se redondea a dos decimales.
   - Se imprime el promedio de presión.

**6.** Si no hay valores válidos se indica que no hay valores para calcular el promedio.

**7.** El programa terminará de manera controlada, ejecutando un return 0 si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.