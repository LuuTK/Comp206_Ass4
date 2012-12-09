#!/usr/bin/python

import cgi
import cgitb 
import sys
import os
import stat

def main():
	# Create instance of FieldStorage 
	form = cgi.FieldStorage() 

	# Get data from fields
	real_name = form.getvalue('rname')
	user_name  = form.getvalue('uname')
	passwd = form.getvalue('passwd')
	email = form.getvalue('email')
	gender = form.getvalue('gender')

	print "Content-type:text/html\r\n\r\n"
	print "<html>"
	print "<head>"
	print "<title>Question 4</title>"
	print "</head>"
	print "<body>"

	if(real_name != None and user_name != None and passwd != None and email != None):
		
		if(verifyUser(user_name) == "yes"):
			addUser(user_name, passwd, real_name, email, "regular")

	else:
		print "Please fill all fields first!"

	print "</body>"
	print "</html>"

def verifyUser(username):
	try:
		f = open("users.csv", "r")
		lines = f.readlines()
		users = []
		
		#Collect all usernames in a list
		for line in lines:
			(u, p, r, e, g) = [x.strip() for x in line.split(',')]
			users.append(u)
		f.close()

		for x in users:
			if x == username:
				print "Error: This username is already taken, please choose another one.."
				return "no"
		
		return "yes"
			
	except:
		print "an error occured at verifyUser..."


def addUser(u, p, r, e, t):
	try:
		f = open("users.csv", "a")
		f.write("%s, %s, %s, %s, %s\r\n" % (u, p, r, e, t))
		print "You have been registered successfully!"
		f.close()
	except:
		print "error occured at addUser"
main()

