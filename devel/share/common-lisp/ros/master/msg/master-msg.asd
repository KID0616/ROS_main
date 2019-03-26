
(cl:in-package :asdf)

(defsystem "master-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "deg" :depends-on ("_package_deg"))
    (:file "_package_deg" :depends-on ("_package"))
  ))