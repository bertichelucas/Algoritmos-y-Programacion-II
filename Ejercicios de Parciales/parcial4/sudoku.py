
def sudoku(cant_elem, M):
    if cant_elem >= 9 ** 2: return True

    cant_elem = sig_pos_a_usar(cant_elem, M)
    if cant_elem >= 9 ** 2: return True

    for num in range(1, 10):
        if puedo_poner(num, cant_elem, M):
            M[fila(cant_elem)[columna(cant_elem)]] = num
            if sudoku(cant_elem, M): return True
        
    M[fila(cant_elem)][columna(cant_elem)] = 0

    return False