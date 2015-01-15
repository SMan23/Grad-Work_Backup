;Suleyman Muhammad
;Graduate Computer Engineer
;Villanova University Class '10
;Villanova Grad Class '11

     ;Homework #3 Source Code and Output (Evaluated Using Allegro CL)
     ;Problems 1-4 Handout Chapter 4: Specialized Data Structures


                    ;**; Problem #1 - Dot Product ;**;

;;;; Function to calculate the dot product

(defun dot_product (vect1 vect2)
  (let ((tmp 0))
  (if (or (not (vectorp vect1)) (not (vectorp vect2))) ; IF !vector return NIL
      nil
    (if (not (eql (length vect1) (length vect2)))      ; IF lengths != return NIL
        nil
      (do ((i (- (length vect1) 1) (- i 1))) ; From i = (length(vect1)-1) to 0
          ((eql i -1) tmp)                   
        ;; Compute tmp = tmp + (vect1(i)*vect2(i))
        (setf tmp (+ tmp (* (svref vect1 i) (svref vect2 i)))))))))

(setf v1 (vector 2 3 4)
      v2 (vector 5 6 0)
      v3 (vector 1/2 2/3 3/4 5/6)
      v4 (vector 2 3/2 4/3 6/5))

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(26): (dot_product v1 v2)
;28
;CG-USER(27): (dot_product v3 v4)
;4
;CG-USER(28): (dot_product '(1 2) '(3 4)) ; ERROR !vector
;NIL

 ;@; ADDITIONAL TESTS

;CG-USER(33): (dot_product v1 v4) ; ERROR lengths !=
;NIL
;CG-USER(34): (dot_product v1 v1) ; v1.*v1 > v1.*v2
;29
;CG-USER(35): (dot_product v3 v3) ; Funny Fraction = 1.951388889
;281/144


                    ;**; Problem #2 - Matrix Addition ;**;

;$$; a)

;;;; RECURSIVE MATRIX ADDITION FUNCTION (Using Lists of Lists)

(defun arrsum (a1 a2)
  (if (null (car a1))
      nil
    (cons (count_col (car a1) (car a2)) (arrsum (cdr a1) (cdr a2)))))

(defun count_col (col1 col2)
  (if (null (car col1))
      nil
    (cons (+ (car col1) (car col2)) (count_col (cdr col1) (cdr col2)))))




;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(31): (arrsum nil nil)
;NIL
;CG-USER(28): (arrsum '((1 2) (3 4)) '((4 3) (2 1)))
;((5 5) (5 5))
;CG-USER(29): (arrsum '((1 2 3) (4 5 6)) '((1 1 1) (2 2 2)))
;((2 3 4) (6 7 8))
;CG-USER(30): (arrsum '((1 2) (3 4) (5 6)) '((6 5) (4 3) (2 1)))
;((7 7) (7 7) (7 7))
;CG-USER(33): (arrsum '((1 2 3 4 5) (5 4 3 2 1)) '((6 7 8 9 10) (10 9 8 7 6)))
;((7 9 11 13 15) (15 13 11 9 7))
;CG-USER(38): (arrsum '((1 1) (2 3) (3 5) (8 13)) '((0 1) (1 2) (5 8) (13 21)))
;((1 2) (3 5) (8 13) (21 34)) ;FIRST EIGHT TERMS OF THE FIBONACCI SEQUENCE

;$$; b)

;;;; MATRIX ADDITION FUNCTION (Using Array Structures)

(defun arrsum2 (a1 a2)
  ;; Create tmp array so that multiple calls to function do not compound
  (setf tmp (make-array (array-dimensions a1) :initial-element 0))
    ;; If the number of dimensions is > 2 or they are not equal dimenisons
    (if (or (> (length (array-dimensions a1)) 2)
            (> (length (array-dimensions a2)) 2)
            (not (equal (length (array-dimensions a1))
                        (length (array-dimensions a2)))))
        nil ; Return NIL
    ;;Assign array dimensions to variables
    (let ((x1 (car (array-dimensions a1)))
          (x2 (car (array-dimensions a2)))
          (y1 (car (cdr (array-dimensions a1))))
          (y2 (car (cdr (array-dimensions a2)))))
      ;; If either dimension is != on the two arrays
      (if (or (not (equal x1 x2))
              (not (equal y1 y2)))
          nil ; Return NIL
        ;; For all i and j where i = x dimension and j = y dimension
        (do ((i 0 (+ i 1)))
            ((eql i x1) tmp) ; Return tmp array
          (do ((j 0 (+ j 1)))
              ((eql j y1))
            ;; Set tmp to a1 + a2
            (setf (aref tmp i j) 
                  (+ (aref a1 i j) (aref a2 i j)))))))))

(defun arrayex (func)
  (setf newarr (make-array '(2 3) :initial-element 0))
  (do ((i 0 (+ i 1)))
      ((eql i 2) newarr)
    (do ((j 0 (+ j 1)))
        ((eql j 3))
      (setf (aref newarr i j) (funcall func i j)))))

(setf ar1 (make-array '(2 3) :initial-element 0))
(setf ar2 (make-array '(2 3) :initial-element 1))
(setf ar3 (arrayex #'+))
(setf ar4 (arrayex #'-))
(setf ar5 (arrayex #'*))
(setf ar6 (arrayex #'(lambda (x y) (* 2 (+ x y)))))







;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(67): (arrsum2 ar1 ar2)
;#2A((1 1 1) (1 1 1))
;CG-USER(68): (arrsum2 ar2 ar3)
;#2A((1 2 3) (2 3 4))
;CG-USER(69): (arrsum2 ar3 ar4)
;#2A((0 0 0) (2 2 2))
;CG-USER(70): (arrsum2 ar4 ar5)
;#2A((0 -1 -2) (1 1 1))
;CG-USER(71): (arrsum2 ar5 ar6)
;#2A((0 2 4) (2 5 8))
;CG-USER(72): (arrsum2 ar2 ar6)
;#2A((1 3 5) (3 5 7))


                    ;**; Problem #3 - String Intersection ;**;

;;;; String Intersection Function

(defun stringint (str1 str2)
  ;; Set len to the length of the shorter string and parse shorter string
  (let ((tmp   "")  ; temporary string variable
        (tmp_p 0 )) ; temporary string position 
    (if (< (length str1) (length str2))
        (setf len   (length str1)
              parse str1
              tmp   str1  ; tmp = str1
              alt   str2) ; Alternate string
        (setf len   (length str2)
              parse str2
              tmp   str2  ; tmp = str2
              alt   str1)); Alternate string
    (if (equal parse "") ; If empty string return empty string
        parse
      (do ((i 0 (+ i 1)))
          ;; When i = len return temp string from 0 upto tmp_p-1 
          ((eql i len) (remove-duplicates (subseq tmp 0 tmp_p))); w/out duplicates
        (progn
          (setf alt_p (position (elt parse i) alt)) ; alt_p = postition of match
          (if alt_p ; If current element in alt
              (progn
                ;; relace tmp(tmp_P) w/ alt(alt_p)
                (setf (char tmp tmp_p) (elt alt alt_p))
                ;; Increment tmp_p
                (setf tmp_p (+ tmp_p 1)))))))))

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(84): (stringint "abc" "abc")
;"abc"
;CG-USER(85): (stringint "trinity" "equality")
;"ity"
;CG-USER(86): (stringint "abc" "cat")
;"ca"
;CG-USER(87): (stringint "bread" "butter")
;"bre"
;CG-USER(88): (stringint "goodbye" "odd")
;"od"
;CG-USER(89): (stringint "Who What" "Where When")
;" Wh"
;CG-USER(90): (stringint "Skills" "Pay Bills")
;"ils"


                    

                    ;**; Problem #4 - Hash Tables ;**;

;;;; Associative Hash Table (i vs. func(i))

(defun hash (func n)
  (do ((i 1 (+ i 1)))
      ((> i n) T)
    ;; Associate iteration with its relative function call
    (setf (gethash i ht) (funcall func i))))

;;; Print Hash table associations

(defun ptable (n)
  (format t "~%**|**~%")
  (do ((i 1 (+ i 1)))
      ((> i n) 'complete) ; Finished
    (format t "~A ~A~%" i (gethash i ht))))

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(65): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x215d7e32>
;CG-USER(66): (hash #'1+ 10)
;T
;CG-USER(67): (ptable 10)
;**|**
;1 2
;2 3
;3 4
;4 5
;5 6
;6 7
;7 8
;8 9
;9 10
;10 11
;COMPLETE

;CG-USER(68): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x2149553a>
;CG-USER(69): (hash #'log 10)
;T
;CG-USER(70): (ptable 5)
;**|**
;1 0.0
;2 0.6931472
;3 1.0986123
;4 1.3862944
;5 1.609438
;COMPLETE

;CG-USER(77): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x2162b7a2>
;CG-USER(78): (hash #'sqrt 10)
;T
;CG-USER(79): (ptable 6)
;**|**
;1 1.0
;2 1.4142135
;3 1.7320508
;4 2.0
;5 2.236068
;6 2.4494898
;COMPLETE



;CG-USER(81): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x2154286a>
;CG-USER(84): (hash #'sin 10)
;T
;CG-USER(85): (ptable 10)
;**|**
;1 0.84147096
;2 0.9092974
;3 0.14112
;4 -0.7568025
;5 -0.9589243
;6 -0.2794155
;7 0.6569866
;8 0.98935825
;9 0.4121185
;10 -0.5440211
;COMPLETE

;CG-USER(86): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x215a1a7a>
;CG-USER(87): (hash #'tan 10)
;T
;CG-USER(88): (ptable 10)
;**|**
;1 1.5574077
;2 -2.1850398
;3 -0.14254655
;4 1.1578213
;5 -3.380515
;6 -0.29100618
;7 0.871448
;8 -6.799711
;9 -0.45231566
;10 0.64836085
;COMPLETE

;CG-USER(89): (setf ht (make-hash-table))
;#<EQL hash-table with 0 entries @ #x214b1e12>
;CG-USER(90): (hash #'cos 10)
;T
;CG-USER(91): (ptable 10)
;**|**
;1 0.5403023
;2 -0.41614684
;3 -0.9899925
;4 -0.6536436
;5 0.2836622
;6 0.96017027
;7 0.75390226
;8 -0.14550003
;9 -0.91113025
;10 -0.8390715
;COMPLETE
