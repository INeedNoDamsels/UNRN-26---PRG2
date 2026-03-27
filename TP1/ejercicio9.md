# 9. Geofencing
### Variables de entrada
- `min` y `max`: Delimitan los límites inferior y superior para la generación de números aleatorios. Son variables de tipo int.
- `x1`, `y1`: Coordenadas iniciales del área generada. Son variables de tipo int.
- `ancho`, `alto`: Dimensiones del área generada. Son variables de tipo int.
- `x2`, `y2`: Coordenadas finales del área calculadas a partir de `x1, y1, ancho, alto`. Son variables de tipo int.

---

### Variables internas
- `rectangulo`: Objeto de tipo `Area` que representa la zona delimitada.
- `ubicacion`: Objeto de tipo `Punto` que representa la posición del dron.
- `i`, `j`: Índices para recorrer el área en la función `imprimirse()`. Son variables de tipo int.
- `x_actual`, `y_actual`: Coordenadas del punto actual mientras se imprime el área. Variables de tipo int.

---

### Variables de salida (implícito)
- Salida por consola:
  - Dimensiones y representación visual del área.
  - Posición del dron (`X`) dentro del área.
  - Mensaje indicando si el dron se encuentra dentro del área o no.
- `return 0`: Indica la finalización correcta del programa.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `obtener()`
- `min <= max`

#### En `Area::tieneA()`
- `x_1 <= x_2` y `y_1 <= y_2`

#### En `main()`
- Los valores aleatorios generados para `x1, y1, ancho, alto` deben ser válidos dentro de los rangos establecidos.
- Las coordenadas calculadas `x2 = x1 + ancho`, `y2 = y1 + alto` deben mantener la integridad del área.

---

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se genera un área rectangular `rectangulo` con dimensiones `ancho x alto`.

**2.** Se genera un dron con coordenadas dentro de un rango extendido alrededor del área.

**3.** Se imprime la representación visual del área:
   - El dron se marca con `X`.
   - El resto del área se representa con espacios vacíos.

**4.** Se verifica la posición del dron con `tieneA()`:
   - Si el dron está dentro del área se imprime "*dron localizado.*"
   - Si el dron está fuera del área se imprime "*no hay rastro del dron.*"

**5.** Todas las coordenadas se calculan de manera consistente.

**6.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.