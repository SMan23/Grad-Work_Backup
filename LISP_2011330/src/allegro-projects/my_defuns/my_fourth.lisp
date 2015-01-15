;Suleyman Muhammad
;1/21/11
;MY-FOURTH LISP src code

(defun my-fourth (lst)
  (let ((size (check-len lst)))
    (if (null lst)                               ;IF not list return NIL
        nil 
        (if (< size 4)                           ;ELSEIF lst < 4 return NIL
            (format t "This list is too short")
            (car (cdr (cdr (cdr lst))))))))      ;ELSE return fourth element

;TEST CODE:
(my-fourth '(a b))      ; FAIL

(check-len '(a b c d e)) ; Returns the number 5 (list length)
(my-fourth '(a b c d e)) ; Returns 4th element D