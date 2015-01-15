;Homework #2 Source Code and Output (Evaluated Using Allegro CL)
;Problems 1-4 Handout Chapter 3: Lists

;All explanations are located within the explanations sheet

                    ;**; Problem #2 - EQUAL vs. EQL ;**;

;$$; a) 3 and (+ 1 1 1)

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(5): (equal 3 (+ 1 1 1))
  ;T

  ;CG-USER(6): (eql 3 (+ 1 1 1))
  ;T


;$$; b) '(1 2) and '(1 2)

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(18): (equal '(1 2) '(1 2))
  ;T

  ;CG-USER(19): (eql '(1 2) '(1 2))
  ;NIL


;$$; c) nil and ()

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(21): (equal nil ())
  ;T

  ;CG-USER(20): (eql nil ())
  ;T


;$$; d) nil and '()

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(22): (equal nil '())
  ;T

  ;CG-USER(24): (eql nil '())
  ;T

;$$; e) 5 and 5

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(26): (equal 5 5)
  ;T

  ;CG-USER(27): (eql 5 5)
  ;T


;$$; f) (cons 'a nil) and '(a)

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(28): (equal (cons 'a nil) '(a))
  ;T

  ;CG-USER(29): (eql (cons 'a nil) '(a))
  ;NIL


;$$; g) (cadr '(a b c)) and 'b

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(30): (equal (cadr '(a b c)) 'b)
  ;T

  ;CG-USER(31): (eql (cadr '(a b c)) 'b)
  ;T


;$$; h) 1.2 and 1.20

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(32): (equal 1.2 1.20)
  ;T

  ;CG-USER(33): (eql 1.2 1.20)
  ;T


;$$; ADDITIONAL TESTS

 ;@; Preliminary Variable/Global/Constat definitions 

     ;(defparameter xTEST 2)
     ;(defconstant  yTEST 2)

     ;(defparameter zTEST '(a))
     ;(defconstant  wTEST '(a))

;$$; i)

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(11): (equal xTEST yTEST)
  ;T

  ;CG-USER(12): (eql xTEST yTEST)
  ;T


;$$; j)

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(16): (equal zTEST wTEST)
  ;T

  ;CG-USER(17): (eql zTEST wTEST)
  ;NIL


;$$; k)

 ;@; COMMAND LINE IN/OUTPUT

 ;CG-USER(21): (equal (cons '(a b) 'c) (cons '(a b) '(c)))
 ;NIL

 
 ;CG-USER(22): (eql (cons '(a b) 'c) (cons '(a b) '(c)))
 ;NIL


                    ;**; Problem #3 - replNZP (replace w/ N Z and P) ;**;
 
;$$; a) Mapcar

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

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(100): (replNZP_mapcar nil)
  ;NIL
  ;CG-USER(101): (replNZP_mapcar '(3))
  ;(P)
  ;CG-USER(102): (replNZP_mapcar '(-1 0 1))
  ;(N Z P)
  ;CG-USER(119): (replNZP_mapcar '(2 (3 -4) (4 5 ((0 -5)))))
  ;(P (P N) (P P ((Z N))))
  ;CG-USER(122): (replNZP_mapcar '(1 0 -1 a 2))
  ;(P Z N A P)
  ;CG-USER(123): (replNZP_mapcar '(1 (a b c) 0 -1 a 2))
  ;(P (A B C) Z N A P)
  ;CG-USER(124): (replNZP_mapcar '(0 a 3 5 i -8))
  ;(Z A P P I N)

;$$; b) Recursive

(defun replNZP_recur (lst)
  (if (null lst) ;return NIL IF list empty
      nil
    (if (listp (car lst))              ;IF element a list call funct on element 
        (cons (replNZP_recur (car lst)) (replNZP_recur (cdr lst)))
      (if (not (numberp(car lst)))          ; IF elemet NOT a NUMBER and keep in place 
          (cons (car lst) (replNZP_recur (cdr lst)))
        (if (> (car lst) 0)                 ; IF element > 0 replace with P
            (cons 'p (replNZP_recur (cdr lst)))
          (if (equal (car lst) 0)           ; IF element = 0 replace with Z
              (cons 'z (replNZP_recur (cdr lst)))
            (cons 'n (replNZP_recur (cdr lst))))))))) ; ELSE replace with N 

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(22): (replNZP_recur nil)
  ;NIL
  ;CG-USER(23): (replNZP_recur '(3))
  ;(P)
  ;CG-USER(24): (replNZP_recur '(-1 0 1))
  ;(N Z P)
  ;CG-USER(25): (replNZP_recur '(2 (3 -4) (4 5 ((0 -5)))))
  ;(P (P N) (P P ((Z N))))
  ;CG-USER(26): (replNZP_recur '(1 0 -1 a 2))
  ;(P Z N A P)
  ;CG-USER(27): (replNZP_recur '(1 (a b c) 0 -1 a 2))
  ;(P (A B C) Z N A P)
  
  ;CG-USER(28): (replNZP_recur '(0 a 3 5 i -8))
  ;(Z A P P I N)


;$$; c) Iterative

(defun replNZP_iter (lst)
  (if (null lst)
      nil
    (do ((lst_var lst (cdr lst_var)) (new_lst nil)) ;DO for every element in loop
        ((null lst_var) (reverse new_lst))          ;return REVERSE new_lst
      (if (listp (car lst_var))     ; If element a list call funct on element
          (setf new_lst (cons (replNZP_iter (car lst_var)) new_lst))
        (if (not (numberp(car lst_var))) ; IF elemet NOT a NUMBER and keep in place 
              (setf new_lst (cons (car lst_var) new_lst))
          (if (> (car lst_var) 0)                ; IF element > 0 replace with P
              (setf new_lst (cons 'p new_lst))
            (if (equal (car lst_var) 0)          ; IF element = 0 replace with Z
                (setf new_lst (cons 'z new_lst))
              (setf new_lst (cons 'n new_lst)))))))))      ; ELSE replace with N 

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(88): (replNZP_iter nil)
  ;NIL
  ;CG-USER(89): (replNZP_iter '(3))
  ;(P)
  ;CG-USER(90): (replNZP_iter '(-1 0 1))
  ;(N Z P)
  ;CG-USER(91): (replNZP_iter '(2 (3 -4) (4 5 ((0 -5)))))
  ;(P (P N) (P P ((Z N))))
  ;CG-USER(92): (replNZP_iter '(1 0 -1 a 2))
  ;(P Z N A P)
  ;CG-USER(93): (replNZP_iter '(1 (a b c) 0 -1 a 2))
  ;(P (A B C) Z N A P)
  ;CG-USER(94): (replNZP_iter '(0 a 3 5 i -8))
  ;(Z A P P I N)


                    ;**; Problem #4 - funcmax ;**;

(defun funcmax (func1 func2 n) ;Function that takes two functions as arguments
  (setf max_vals nil)          ;Initialize max_vals
    (do ((i 1 (+ i 1)))        ;from i = 1 ... n
        ((> i n) (reverse max_vals))
      (progn
        (setf val1 (funcall func1 i)  ;val1 = funct1(i)
              val2 (funcall func2 i)) ;val2 = funct2(i)
        (if (> val1 val2)      ;IF val1 > val2 RETURN val1 ELSE RETURN val2
            (setf max_vals (cons (cons i val1) max_vals))
            (setf max_vals (cons (cons i val2) max_vals))))))

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(50): (funcmax #'1+ #'1- 3)
  ;((1 . 2) (2 . 3) (3 . 4))
  ;CG-USER(51): (funcmax #'(lambda (x) (* 2 x)) #'(lambda (x) (* -2 (- x 4))) 10)
  ;((1 . 6) (2 . 4) (3 . 6) (4 . 8) (5 . 10) (6 . 12) (7 . 14) (8 . 16) (9 . 18) (10 . 20))

 







 ;@; Test Functions F vs. G  "sin(n*pi/4) vs. cos(n*pi/4)"

(defun f (n)
  (sin (* n (/ pi 4))))

(defun g (n)
  (cos (* n (/ pi 4))))

  ;CG-USER(52): (funcmax #'f #'g 8)
  ;((1 . 0.7071067811865476d0) (2 . 1.0d0) (3 . 0.7071067811865476d0) (4 . 1.2246063538223773d-16)
  ; (5 . -0.7071067811865475d0) (6 . -1.836909530733566d-16) (7 . 0.7071067811865474d0) (8 . 1.0d0))

           ;@@; ADDITIONAL TESTS ;@@;

  ;#; REVISED FUNCMAX

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

 ;@; Test Functions H vs. I  "e^n vs. 2^n"

(defun h (n)
  (exp n))    ; e^n

(defun i (n)
  (expt 2 n)) ; 2^n

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(49): (setf x (funcmax #'h #'i 10))
  ;((1 2.7182817 . FUNCT1) (2 7.389056 . FUNCT1) (3 20.085537 . FUNCT1) (4 54.59815 . FUNCT1)
  ; (5 148.41316 . FUNCT1) (6 403.4288 . FUNCT1) (7 1096.6332 . FUNCT1) (8 2980.958 . FUNCT1)
  ; (9 8103.084 . FUNCT1) (10 22026.465 . FUNCT1))
  
 ;@; Test Functions H vs. J  "e^n vs. 3^n" 

(defun j (n)
  (expt 3 n)) ; 3^n

 ;@; COMMAND LINE IN/OUTPUT

  ;CG-USER(50): (setf y (funcmax #'h #'j 10))
  ;((1 3 . FUNCT2) (2 9 . FUNCT2) (3 27 . FUNCT2) (4 81 . FUNCT2) (5 243 . FUNCT2) (6 729 . FUNCT2)
  ; (7 2187 . FUNCT2) (8 6561 . FUNCT2) (9 19683 . FUNCT2) (10 59049 . FUNCT2))

 ;@; ASSOCIATION TEST
  
  ;CG-USER(51): (assoc '2 x)
  ;(2 7.389056 . FUNCT1)

  ;CG-USER(52): (assoc '4 y)
  ;(4 81 . FUNCT2)
