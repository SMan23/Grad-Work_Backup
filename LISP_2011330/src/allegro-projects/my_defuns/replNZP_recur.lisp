;Suleyman Muhammad
;Graduate Computer Engineer
;Villanova University

;Function that replaces every negative integer, zero, and positive integer 
;by N Z and P respectively. This function uses recursion.

(defun replNZP_recur (lst)
  (if (null lst) ;return NIL IF list empty
      nil
    (if (listp (car lst))              ;IF element not an atom call funct on car 
        (cons (replNZP_recur (car lst)) (replNZP_recur (cdr lst)))
      (if (not (numberp(car lst)))          ; IF elemet NOT a NUMBER and keep in place 
          (cons (car lst) (replNZP_recur (cdr lst)))
        (if (> (car lst) 0)                 ; IF element > 0 replace with P
            (cons 'p (replNZP_recur (cdr lst)))
          (if (equal (car lst) 0)           ; IF element = 0 replace with Z
              (cons 'z (replNZP_recur (cdr lst)))
            (cons 'n (replNZP_recur (cdr lst))))))))) ; ELSE replace with N 

;(replNZP_recur nil)

;(replNZP_recur '(3))

;(replNZP_recur '(-1 0 1))

;(replNZP_recur '(2 (3 -4) (4 5 ((0 -5)))))

;(replNZP_recur '(1 0 -1 a 2))

;(replNZP_recur '(1 (a b c) 0 -1 a 2))

;(replNZP_recur '(0 a 3 5 i -8))