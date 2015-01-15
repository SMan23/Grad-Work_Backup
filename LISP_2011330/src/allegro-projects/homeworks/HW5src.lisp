;Suleyman Muhammad
;Graduate Computer Engineer
;Villanova University Class '10
;Villanova Grad Class '11

     ;Homework #5 Source Code and Output (Evaluated Using Allegro CL)
     ;Problems Chapter 7: LISP I/O

     
                    ;**; Problem #1 -  strings2file ;**;

;;;; Functions that read any number of strings from stdin and writes it to a file

;;; Flagship Function which reads the line from standard input and passes to main

(defun strings2file (filename)         ; Input to the function is the file name
    (parse_line (read-line) filename)) ; Read line from stdin and pass file name

;;; Main Function which parses the line and writes it to the file

(defun parse_line (line filename)
  (let ((file (make-pathname :name filename)) ; Initialize pathname
        (len (length line))                   ; Length of line
        (buf   " "))                          ; Character buffer
    (with-open-file (stream file :direction :output ; Open file for writing
                            :if-exists :supersede)
    ;;For length of line  
    (do ((pos 0 (1+ pos))) 
        ((eql pos len) t)
      (progn
        (setf tmp (char line pos))
        (setf (char buf 0) tmp)
        (if (equal buf " ")
            (format stream "~%")         ; Write newline to file
          (format stream "~A" buf))))))) ; Write char to file

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(7): (strings2file "myfile")
;hello buddy how are you
;
;T

  ;@; FILE CONTENTS

;[suleyman@Ubuntu-10  T1:LvL1:C2005:J0  Mon Mar 21 2011 02:59:00 EDT]
;~/LISP/src/allegro-projects/homeworks$ cat myfile
;hello
;buddy
;how
;are
;you
















                    ;**; Problem #2 -  file2list ;**;

;;;; Function that reads strings from a file and creates a list

(defun file2list (filename)  ; Input to function is the file name
  (let ((file (make-pathname :name filename)) ; Initialize path
        (str_list nil))                       ; String list
    (with-open-file (stream_o file :direction :input) ; Open file for reading
      ;; For the length of file
      (do ((line (read-line stream_o nil 'eof)   ; Return eof if end of file
                 (read-line stream_o nil 'eof)))
          ;; Exit if eof returned from read and return completed list 
          ((eql line 'eof) (setf str_list (reverse str_list)))
        ;;Compile list of strings
        (setf str_list (cons line str_list))))))

;@; COMMAND LINE INPUT/OUTPUT

;CG-USER(13): (file2list "myfile")
;("hello" "buddy" "how" "are" "you")

