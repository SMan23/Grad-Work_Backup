;Suleyman Muhammad
;1/12/11
;CHECK-LEN ITERATIVE src code

(defun check-len (lst)
  (let ((len 0))
  (if (null lst)
      nil
      (do ((i 0 (+ i 1)))
          ((null lst) len)
        (setf lst (cdr lst) 
              len (+ len 1))))))



;TEST CODE:
;(check-len '(a b c d e))