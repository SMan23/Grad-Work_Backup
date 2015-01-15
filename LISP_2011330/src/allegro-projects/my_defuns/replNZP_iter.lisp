(defun replNZP_iter (lst)
  (if (null lst)
      nil
    (do ((lst_var lst (cdr lst_var)) (new_lst nil)) ;DO for every element in loop
        ((null lst_var) (reverse new_lst))          ;return REVERSE new_lst
      (if (listp (car lst_var))      ; If element NOT atom call funct on car lst
          (setf new_lst (cons (replNZP_iter (car lst_var)) new_lst))
        (if (not (numberp(car lst_var)))  ; IF elemet NOT a NUMBER and keep in place 
              (setf new_lst (cons (car lst_var) new_lst))
          (if (> (car lst_var) 0)                ; IF element > 0 replace with P
              (setf new_lst (cons 'p new_lst))
            (if (equal (car lst_var) 0)          ; IF element = 0 replace with Z
                (setf new_lst (cons 'z new_lst))
              (setf new_lst (cons 'n new_lst)))))))))      ; ELSE replace with N  


;(replNZP_iter nil)

;(replNZP_iter '(3))

;(replNZP_iter '(-1 0 1))

;(replNZP_iter '(2 (3 -4) (4 5 ((0 -5)))))

(replNZP_iter '(1 0 -1 a 2))

(replNZP_iter '(1 (a b c) 0 -1 a 2))

(replNZP_iter '(0 a 3 5 i -8))