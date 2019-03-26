;; Auto-generated. Do not edit!


(when (boundp 'master::deg)
  (if (not (find-package "MASTER"))
    (make-package "MASTER"))
  (shadow 'deg (find-package "MASTER")))
(unless (find-package "MASTER::DEG")
  (make-package "MASTER::DEG"))

(in-package "ROS")
;;//! \htmlinclude deg.msg.html


(defclass master::deg
  :super ros::object
  :slots (_deg ))

(defmethod master::deg
  (:init
   (&key
    ((:deg __deg) 0)
    )
   (send-super :init)
   (setq _deg (round __deg))
   self)
  (:deg
   (&optional __deg)
   (if __deg (setq _deg __deg)) _deg)
  (:serialization-length
   ()
   (+
    ;; uint16 _deg
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint16 _deg
       (write-word _deg s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint16 _deg
     (setq _deg (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get master::deg :md5sum-) "37c3b1a681be3c306e3679e4da1932c3")
(setf (get master::deg :datatype-) "master/deg")
(setf (get master::deg :definition-)
      "uint16 deg

")



(provide :master/deg "37c3b1a681be3c306e3679e4da1932c3")


