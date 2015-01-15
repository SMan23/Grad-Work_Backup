(defun my-third (x)
  (car (cdr (cdr x))))

(defun add-third (obj lst)
  (+ obj (my-third lst)))