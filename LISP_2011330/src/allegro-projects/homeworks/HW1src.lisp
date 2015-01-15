;Homework #1 Source Code and Output (Evaluated Using Allegro CL)
;Problems 1-9 pg. 29


          ;**; Problem #1 - Describe whtat happens ;**; 

;$$; a)

;@; Command Line INPUT and OUTPUT 

;CG-USER(3): (+ (- 5 1) (+ 3 7))
;14


;$$; b)

;@; Command Line INPUT and OUTPUT

;CG-USER(4): (list 1 (+ 2 3))
;(1 5)


;$$; c)

;@; Command Line INPUT and OUTPUT

;CG-USER(5): (if (listp 1) (+ 1 2) (+ 3 4))
;7

;$$; d)

;@; Command Line INPUT and OUTPUT

;CG-USER(14): (list (and (listp 3) t) (+ 1 2))
;(NIL 3)


          ;**; Problem #2 - Give 3 different Cons expressions  ;**;
          ;**;              which return (A B C)               ;**;

;$$; 1)

;@; Command Line INPUT and OUTPUT

;CG-USER(22): (cons 'a '(b c))
;(A B C)

;$$; 2)

;@; Command Line INPUT and OUTPUT

;CG-USER(2): (cons 'a (cons 'b '(c)))
;(A B C)

;$$; 3)

;@; Command Line INPUT and OUTPUT

;CG-USER(4): (cons 'a (cons 'b (cons 'c nil)))
;(A B C)


          ;**; Problem #3 - Using car and cdr, define function ;**;
          ;**;              to return the forth element        ;**;

;MY-FOURTH LISP src code

(defun my-fourth (lst)
  (let ((size (check-len lst)))               ;store list-len in size
    (if (null lst)                            ;IF empty list return NIL
        nil 
      (if (< size 4)                          ;ELSEIF size < 4 PRINT error
          (format t "This list is too short")
        (car (cdr (cdr (cdr lst))))))))       ;ELSE return fourth element

(defun check-len (lst) ;Function which returns the length of a list
  (let ((len 0))
    (if (null lst)
        nil
      (do ((i 0 (+ i 1)))
          ((null lst) len)
        (setf lst (cdr lst) 
              len (+ len 1))))))

;@; Function Test

;(my-fourth '(a b))       ; Prints error msg
;(check-len '(a b c d e)) ; Returns the number 5 (list length)
;(my-fourth '(a b c d e)) ; Returns 4th element D

         ;**; Problem #4 - Function that returns the greater ;**;
         ;**;              of two integers                   ;**;

(defun greater (x y)
  (if (or (not (numberp x)) (not (numberp y)))
      (format t "Input Numbers Please")  ;IF x || y are NOT numbers PRINT error
    (if (> (- x y) 0)                    ;ELSE IF x-y > 0
        x                                ;return x
      y)))                               ;ELSE return y

;@; Function Test
;(greater 6 10)

;@; OUTPUT:
;CG-USER(37): 
;10


          ;**; Problem #5 - Describe Following Functions ;**;

;$$; a)

(defun enigma (x)
  (format t "enigma: x = ~A~%" x) ;PRINT test msg
  (and (not (null x))
       (or (null (car x))
           (enigma (cdr x)))))

;@; Function Test

;(enigma '(a b c))

;@; OUTPUT:
;CG-USER(3): enigma: x = (A B C)
;enigma: x = (B C)
;enigma: x = (C)
;enigma: x = NIL
;NIL

;$$; b)

(defun mystery (x y)
  (format t "mystery: x = ~A, y = ~A~%" x y) ;PRINT test msg
  (if (null y)
      nil
    (if (eql (car y) x)
        0
      (let ((z (mystery x (cdr y))))
        (and z (+ z 1))))))

;@;Function Test

;(mystery 3 '(1 2 3 4 5))

;@;OUTPUT:
;CG-USER(20): mystery: x = 3, y = (1 2 3 4 5)
;mystery: x = 3, y = (2 3 4 5)
;mystery: x = 3, y = (3 4 5)
;2


          ;**; Problem #6 - Replace x ;**;

;$$;a) (car (x (cdr '(a (b c) d))))

;(car (car (cdr '(a (b c) d)))) ;REPLACED x with CAR

;@;OUTPUT:
;CG-USER(21): 
;B

;$$;b) (x 13 (/ 1 0)) 

;(or 13 (/1 0)) ;REPLACED x with OR

;@;OUTPUT:
;CG-USER(22): 
;13

;$$;c) (x #'list 1 nil)

;(apply #'list 1 nil) ; REPLACED x with APPLY

;@;OUTPUT:
;CG-USER(3): 
;(1)


          ;**; Problem #7 - Function to find a list in a list ;**;

(defun list-in-list (lst)
  (if (null lst)                  
      (format t "This list is empty or does not contain a list ~%")
    (if (listp (car lst))         ;IF object in list is a list
        T                         ;return T
      (list-in-list (cdr lst))))) ;ELSE call function on (cdr lst)

;@;Function Test

;(list-in-list '(a b c d))

;;OUTPUT:
;CG-USER(2): This list is empty or does not contain a list 
;NIL

;(list-in-list '(a (b c) d))

;@;OUTPUT:
;CG-USER(9): 
;T


          ;**; Problem #8 - Iterative and Recursive Definitions ;**;

;$$; a) Function to take a postiive integer and prints that many dots 

;;ITERATIVE

(defun iter-dots (num)
  (if (not (typep num 'integer))         ;IF number not an integer
      (format t "Please use an integer") ;PRINT error
    (do ((i num (- i 1)))                ;ELSE from num downto 0
        ((eql i 0) (format t "~A dots" num))
      (format t ". "))))                 ;PRINT a dot

;@; Function Test

;(iter-dots '(d))

;@; OUTPUT:
;CG-USER(59): Please use an integer
;NIL

;(iter-dots 8)

;@; OUTPUT:
;CG-USER(69): . . . . . . . . 8 dots
;NIL

;;RECURSIVE

(defun recur-dots (num)
  (if (not (typep num 'integer))         ;IF number not an integer
      (format t "Please use an integer") ;PRINT error msg
      (if (eql num 0)                    ;ELSE until num = 0
          'done
          (progn
            (format t ". ")              ;PRINT a dot
            (recur-dots (- num 1))))))

;@; Function Test

;(recur-dots 5)

;@; OUTPUT;
;CG-USER(78): . . . . . 
;DONE

;$$; b) A function that takes a list and returns 
;$$;    the times the symbol a occurs

;; ITERATIVE

(defun find-a-iter (lst)
  (let ((sum 0) (val 'a))           ;Initialize SUM and VAL
    (if (null lst)                  ;IF empty list return NIL
        nil
      (dolist (obj lst)             ;ELSE for every OBJ in LST
        (if (eql obj val)           ;IF OBJ = VAL
            (setf sum (+ sum 1))))) ;Increment SUM
    (format t "Symbol ~A occurs ~A times~%" val sum)))

;@; Function Test

;(find-a-iter '(a b a c a))

;@; OUTPUT:
;CG-USER(35): Symbol A occurs 3 times
;NIL

;; RECURSIVE

(defun find-a-recur (lst)
  (let ((val 'a))
    (if (null lst)         ;IF empty list return NIL
        nil
      (if (null (cdr lst)) ;ELSE IF last element 
          (if (eql (car lst) val) ;IF last element = VAL
              1                              ;return 1
              0)                             ;ELSE return 0
          (if (eql (car lst) val) ;ELSE IF NOT last element
              (+ (find-a-recur (cdr lst)) 1) ;IF element = VAL call function+1
              (find-a-recur (cdr lst)))))))  ;ELSE call function
        
;@; Function Test

;(find-a-recur '(a b a c a))

;@; OUTPUT:   
;CG-USER(7): 
;3


          ;**; Problem #9 - Correct the given CODE ;**;

;$$; a)
;;CORRECT CODE

(defun summit (lst)
  (setf lst (remove nil lst))
  (apply #'+ lst))

;@; Function Test

;(summit '(1 3 4 nil 5))

;@; OUTPUT:
;CG-USER(9): 
;13

;$$; b)
;;CORRECT CODE

(defun summit2 (lst)
  (let ((x (car lst)))
    (if (null x)
        (if (null (cdr lst))
            0
          (summit (cdr lst)))
      (+ x (summit (cdr lst))))))

;@; Function Test`

;(summit2 '(1 3 4 nil 5))

;@; OUTPUT:
;CG-USER(11): 
;13









