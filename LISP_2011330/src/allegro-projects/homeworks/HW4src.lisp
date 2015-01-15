;Suleyman Muhammad
;Graduate Computer Engineer
;Villanova University Class '10
;Villanova Grad Class '11

     ;Homework #4 Source Code and Output (Evaluated Using Allegro CL)
     ;Problems 1-3 Handout Chapter 5: Control

     ;All explanations are located within the explanations sheet


                    ;**; Problem #1 -  test -> test2 ;**;

;;;; Functions to test the type of elements within a list

;;; Original: test

(defun test (elt)
  (if (numberp elt) 
      (if (< 0 elt) 'p
        (if (> 0 elt) 'n 'z))
    (if (atom elt) 'a
      (if (listp elt) 'l 'unknown))))

;;; Revision: test2

(defun test2 (elt)
  (cond ((numberp elt) (cond ((< 0 elt) 'p)
                             ((> 0 elt) 'n)
                             (t 'z)))
        (t (cond ((atom elt) 'a)
                 ((listp elt) 'l)
                 (t 'unknown)))))
         

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(1): (test 'a)
;A
;CG-USER(2): (test 3)
;P
;CG-USER(3): (test -3)
;N
;CG-USER(4): (test '(a b c))
;L
;CG-USER(9): (mapcar #'test '(-1 0 1 b (a b c) (2.3)))
;(N Z P A L L)
;CG-USER(10): (mapcar #'test '(nil (vector 123) (make-array '(2 4) :initial-element 0)
;                     (make-hash-table)))
;(A L L L)

;CG-USER(6): (test2 'a)
;A
;CG-USER(7): (test2 3)
;P
;CG-USER(8): (test2 -3)
;N
;CG-USER(9): (test2 '(abc))
;L
;CG-USER(12): (mapcar #'test2 '(-1 0 1 b (a b c) (2.3)))
;(N Z P A L L)
;CG-USER(2): (mapcar #'test2 '(nil (vector 123) (make-array '(2 4) :initial-element 0)
;                     (make-hash-table)))
;(A L L L)

 

 ;@; ADDITIONAL TESTS

;CG-USER(21): (test 2332)
;P
;CG-USER(22): (test '(6 a (7 b)))
;L
;CG-USER(23): (mapcar #'test '(1f3))
;(P)
;CG-USER(24): (mapcar #'test '(f13))
;(A)
;CG-USER(25): (mapcar #'test '(1g3))
;(A)
;CG-USER(26): (mapcar #'test '(15 f g (a b 1) (c . d)))
;(P A A L L)
;CG-USER(27): (test2 2332)
;P
;CG-USER(28): (test2 '(6 a (7 b)))
;L
;CG-USER(29): (mapcar #'test2 '(1f3))
;(P)
;CG-USER(30): (mapcar #'test2 '(f13))
;(A)
;CG-USER(31): (mapcar #'test2 '(1g3))
;(A)
;CG-USER(32): (mapcar #'test2 '(15 f g (a b 1) (c . d)))
;(P A A L L)


                    ;**; Problem #2 - mods -> mods2 -> mods3 ;**;

;;;; RECURSIVE MATRIX ADDITION FUNCTION (Using Lists of Lists)

;;; Original: mods

(defun mods (lst n)
  (cond ((null lst) nil)
        ((zerop (mod (car lst) n)) (cons 0 (mods (cdr lst) (+ 1 n))))
        (t (cons n (mods (cdr lst) n)))))

;;; Recursive Revision: mods2

(defun mods2 (lst n)
  (amods2 lst n nil))

(defun amods2 (lst n lst2)
  (cond ((null lst) (reverse lst2))
        ((zerop (mod (car lst) n)) (amods2 (cdr lst) (+ n 1) (cons 0 lst2)))
        (t (amods2 (cdr lst) n (cons n lst2)))))

;;; Iterative Revision: mods3

(defun mods3 (lst n)
  (let ((lst2 nil))
    (do ((i lst (cdr i)))
        ((eql i nil) (reverse lst2))
      (if (zerop (mod (car i) n))
          (setf lst2 (cons 0 lst2)
                n (+ n 1))
          (setf lst2 (cons n lst2))))))

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(10): (mods nil 2)
;NIL
;CG-USER(11): (mods '(3 4 5) 3)
;(0 0 0)
;CG-USER(12): (mods '(2 3 5 4) 3)
;(3 0 4 0)
;CG-USER(25): (mods '(15 3 10 20 4) 5)
;(0 6 6 6 6)
;CG-USER(27): (mods '(10 18 28 24) 5)
;(0 0 0 0)
;CG-USER(28): (mods '(4 3 10 23 32 6) 8)
;(8 8 8 8 0 9)
;CG-USER(29): (mods '(4 7 6 21 8 12 50) 2)
;(0 3 0 4 0 5 0)
;CG-USER(30): (mods '(3 5 82 12 49) 7)
;(7 7 7 7 0)
;CG-USER(31): (mods '(2 3 4 5 6 7) 8)
;(8 8 8 8 8 8)

;CG-USER(22): (mods2 nil 2)
;NIL
;CG-USER(23): (mods2 '(3 4 5) 3)
;(0 0 0)
;CG-USER(24): (mods2 '(2 3 5 4) 3)
;(3 0 4 0)
;CG-USER(26): (mods2 '(15 3 10 20 4) 5)
;(0 6 6 6 6)
;CG-USER(32): (mods2 '(10 18 28 24) 5)
;(0 0 0 0)
;CG-USER(33): (mods2 '(4 3 10 23 32 6) 8)
;(8 8 8 8 0 9)
;CG-USER(34): (mods2 '(4 7 6 21 8 12 50) 2)
;(0 3 0 4 0 5 0)
;CG-USER(35): (mods2 '(3 5 82 12 49) 7)
;(7 7 7 7 0)
;CG-USER(36): (mods2 '(2 3 4 5 6 7) 8)
;(8 8 8 8 8 8)

;CG-USER(22): (mods3 nil 2)
;NIL
;CG-USER(23): (mods3 '(3 4 5) 3)
;(0 0 0)
;CG-USER(24): (mods3 '(2 3 5 4) 3)
;(3 0 4 0)
;CG-USER(25): (mods3 '(15 3 10 20 4) 5)
;(0 6 6 6 6)
;CG-USER(26): (mods3 '(10 18 28 24) 5)
;(0 0 0 0)
;CG-USER(27): (mods3 '(4 3 10 23 32 6) 8)
;(8 8 8 8 0 9)
;CG-USER(28): (mods3 '(4 7 6 21 8 12 50) 2)
;(0 3 0 4 0 5 0)
;CG-USER(29): (mods3 '(3 5 82 12 49) 7)
;(7 7 7 7 0)
;CG-USER(30): (mods3 '(2 3 4 5 6 7) 8)
;(8 8 8 8 8 8)


                    ;**; Problem #3 - Expression Analysis ;**;

;@; COMMAND LINE INPUT/OUTPUT
;$$; (a
;CG-USER(10): (or (listp 'a) (numberp 3) (> 0 -2))
;T

;$$; (b
;CG-USER(11): (and (numberp 'a) (listp '(1 2 3)))
;NIL

;$$; (c
;CG-USER(12): (and (numberp 2) (atom 'b) (+ 3 5))
;8

;$$; (d
;CG-USER(13): (if (> 100 101) (+ 4 5) (- 2 3))
;-1

 ;@; ADDITIONAL TESTS

;$$; (e
;CG-USER(5): (when 5
;  (format t "~A " (cons 'equivalent nil))
;  (listp '(5 (listp '(32))))
;  (format t "~A " 'to)
;  nil
;  (format t "~A " 'conditional)
;  23
;  (format t "~A " 'progn) t)
;              
;(EQUIVALENT) TO CONDITIONAL PROGN 
;T

;$$; (f
;CG-USER(6): (if (not (typep 'y 'integer)) 'not_integer 'integer)
;NOT_INTEGER

;$$; (g
;CG-USER(8): (or nil 6 'will_not_see)
;6

;$$; (h
;CG-USER(10): (let ((x 5) (y 10)) (if (> x y) 'x_grtr 'y_grtr))
;Y_GRTR
