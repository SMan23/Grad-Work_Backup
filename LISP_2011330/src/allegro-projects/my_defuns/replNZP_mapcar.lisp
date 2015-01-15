(defun replNZP_mapcar (lst)
  (mapcar #'(lambda (elt) 
              (if (listp elt)          ;IF element a list call funct on element
                  (replNZP_mapcar elt)
                (if (not (numberp elt));IF element not number return element
                    elt
                  (if (> elt 0)        ;IF element > 0 return P
                      'p
                    (if (eql elt 0)    ;IF element = 0 return Z
                        'z
                        'n))))) lst))   ;ELSE return N

;(replNZP_mapcar nil)

;(replNZP_mapcar '(3))

;(replNZP_mapcar '(-1 0 1))

;(replNZP_mapcar '(2 (3 -4) (4 5 ((0 -5)))))

;(replNZP_mapcar '(1 0 -1 a 2))

(replNZP_mapcar '(1 (a b c) 0 -1 a 2))

(replNZP_mapcar '(0 a 3 5 i -8))