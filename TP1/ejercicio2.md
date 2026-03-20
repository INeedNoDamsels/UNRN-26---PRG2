## 1. Trayectoria de Proyectiles
### Variables de entrada
- `H`: Indica la altura, en metros,  de un muro. Es una variable de tipo float.
- `D`: Indica la distancia, en metros, del muro en relación al dispositivo que lanza el objeto. Es una variable de tipo float.
- `v`: Indica la velocidad inicial, en metros sobre segundos, de un objeto al ser lanzado por un dispositivo. Es una variable de tipo float.
- `t`: Indica el ángulo de tiro del objeto lanzado. Es una variable de tipo float.

### Variables de salida
- `resultado`: Indica la altura del objeto al llegar a la misma distancia que el muro. Es una variable de tipo float.

---

### Precondiciones
*Los requisitos previos para la ejecución del programa.*

#### En `validarIngreso()`
- `valor` ∈ ℝ
- `valor` > 0
#### En `main()`
- `H ∈ ℝ` y `H > 0`
- `D ∈ ℝ` y `D > 0`
- `v ∈ ℝ` y `v > 0`
- `t ∈ ℝ` y `t > 0`

### Postcondiciones
*Los resultados que se garantizan obtener luego de la ejecución del programa.*

**1.** Se calculará correctamente la altura del objeto lanzado cuando este se encuentre a la misma distancia D que separa al muro del dispositivo.
- `resultado` = `D` × `tan(t)` - (9.81 × `D`²) / (2 × `v`² × `cos(t)`²);

**2.** Se informará qué ocurrirá con el objeto lanzado.
- Si `resultado < H`, se imprimirá “*el proyectil va a chocar contra el muro*”.
- Si `resultado = H`, se imprimirá “*el proyectil va a rozar el muro*”.
- Si `resultado > H`, se imprimirá “*el proyectil va a superar el muro*”.

**3.** El programa terminará de manera controlada, ejecutando un `return 0` si todos los datos ingresados son válidos, cumplen con las precondiciones establecidas y los cálculos se realizaron correctamente.