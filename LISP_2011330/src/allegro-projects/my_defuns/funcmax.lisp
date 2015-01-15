(defun funcmax (func1 func2 n) ;Function that takes two functions as arguments
  (setf max_vals nil)          ;Initialize max_vals
    (do ((i 1 (+ i 1)))        ;from i = 1 ... n
        ((> i n) (reverse max_vals))
      (progn
        (setf val1 (funcall func1 i)  ;val1 = funct1(i)
              val2 (funcall func2 i)) ;val2 = funct2(i)
        (if (> val1 val2)      ;IF val1 > val2 RETURN val1 ELSE RETURN val2
            (setf max_vals (cons (cons i (cons val1 'funct1)) max_vals))
            (setf max_vals (cons (cons i (cons val2 'funct2)) max_vals))))))

;(funcmax #'1+ #'1- 3)

;(funcmax #'(lambda (x) (* 2 x)) #'(lambda (x) (* -2 (- x 4))) 10)

(defun f (n)
  (sin (* n (/ pi 4))))

(defun g (n)
  (cos (* n (/ pi 4))))

;(funcmax #'f #'g 8)

(defun h (n)
  (exp n))

(defun i (n)
  (expt 2 n))

;(funcmax #'h #'i 10)