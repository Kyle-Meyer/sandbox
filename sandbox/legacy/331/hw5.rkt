#lang racket
( define course-list (cons '("Dept" "Number" "Section" "Class Nbr" "Capacity" "Enrollment")
                             '(("CMSC" "201" "1" "1052" 100 30)
                             ("CMSC" "341" "6" "7447" 40 27)
                             ("CMSC" "341" "3" "7443" "40" 29)
                             ("CMSC" "331" "5" "7746" 40 36)
                             ("CMSC" "331" "6" "7747" 40 "40")
                             ("CMSC" "471" "3" "8196" 40 31))
                             
                      )
)

#|
define a function as (open-seats section)
section is a member of course-list
in this function we calculate the available seats by deducting Enrollement from Capacity
and we prepare a string to be printed to the standard output in the following form:
CMSC341 (Section 6) => 13
|#

(define (open-seats section)
  (define x (list-ref section 4))
  (define y (list-ref section 5))
  (define z (- x y))
  (define (print out)
     (string-append out (list-ref section 0) (list-ref section 1) " (Section " (list-ref section 2) ") => " (number->string z))
   )
  (if (positive? z) (displayln(print "")) "") 
)

#|
define a function as (report-open-seats course-list)
In this function we iterate through course-list
for every course record we need to check whether both Enrollment and Capacity are numbers
If both are numbers then we call the function (open-seats ...) on the course record
if any of them is not a number we just ignore the record
and we print the returned string to the standard output
the result for every record should be printed on a new line
|#

(define (report-open-seats lst)
  (unless (empty? lst)
    (define x (list-ref(car lst) 4))
    (define y (list-ref(car lst) 5))
    (if (number? x)
        (if (number? y)
            (open-seats (car lst))
        "")"")
    ;
    ;(displayln (number? x))
    ;(displayln "")
    (report-open-seats (cdr lst))))
  

; leave the following function call intact
(report-open-seats course-list)
