#!/usr/bin/python

import cgi

def checkUser(username, password):
	members=open("members.csv","r")
	membersList=members.readlines()
	"""creating an array in which each cell is a line from the file"""
	exists=0
	checking=1
	while(checking):
		for i in range(len(membersList)):
			"""scanning the whole file array"""
			lineInfo=membersList[i].split()
			"""making an array out of every line; each cell represents a string"""
			""".split() is used to separate the strings"""
			tempUser=lineInfo[0].replace(",","")
			tempPass=lineInfo[1].replace(",","")
			"""removing the comma by replacing with 'null'"""
			if(username==tempUser and password==tempPass):
				"""checking if the username and password exist"""
				exists=1
				checking=0
				""""checking to 0 to stop the while loop"""
				"""exists will be returned"""
			else:
				if(i==len(membersList)-1 and exists==0):
					print "user not found"
					checking=0
	members.close()
	return exists

def billing(model, amount):
    import csv
    amount=int(amount)
    inventory=open("inventory.csv","r")
    inventList=inventory.readlines()
    for i in range(len(inventList)):
        tempLine=inventList[i].split()
        if model==tempLine[1].replace(",",""):
            amountAvailable=tempLine[3].replace(",","")
            if amount<=int(amountAvailable):
                """checking if the amount to purchase is valid"""
                price=int(tempLine[4])*amount
                """tempLine[4] represents the price. It is casted into an int prior to multiplying"""
                amountRemaining=int(amountAvailable)-amount
                """updating the amount remaining. Will have to append this value later"""
                tempLine[3]=amountRemaining
                inventList[i]="%s %s %s %s, %s \n" % (tempLine[0], tempLine[1], tempLine[2], tempLine[3], tempLine[4])
                inventory.close()


                adding=open("inventory.csv", "w")
                for j in range(len(inventList)):
		    adding.write(inventList[j])	
                adding.close()


                return price
            else:
                amount=int(amountAvailable)
                """if amount entered exceeds maximum, it is modified to amountAvailable"""
                price=amount*int(tempLine[4])
                inventList[i]="%s %s %s 0, %s \n" % (tempLine[0], tempLine[1], tempLine[2], tempLine[4])
                inventory.close()

                adding=open("inventory.csv", "w")
                for j in range(len(inventList)):
		    adding.write(inventList[j])	
                adding.close()

                return price

def appendAmount(username, amount):
	import csv
        log=open("log.csv","r")
        logList=log.readlines()
        for i in range(len(logList)):
                logLine=logList[i].split()
                tempUser=logLine[0].replace(",","")
                if(username==tempUser):
                        temp=int(logLine[1])+amount
                        logList[i]="%s %s \n" % (logLine[0], temp)
        log.close()

	adding=open("log.csv", "w")
	for j in range(len(logList)):
		adding.write(logList[j])	
	adding.close()

def main():
	print "Content-type:text/html\n\n"
	print """<body background="road.jpg">"""
        form=cgi.FieldStorage()
        SLKPrice=0
        SLSPrice=0
        aventPrice=0
        """prices are initialized to 0"""
        if (form==""):
                print "Error!"
        elif (form.has_key('username') and form.has_key('password') and (form["username"].value!="" and form["password"].value!="")):
                """checking if there's a username & password, and then if they're correct"""
                if checkUser(form["username"].value, form["password"].value):
                        if (form.has_key('checkboxSLK') and form["checkboxSLK"].value=="on"):
                                SLKPrice=int(billing("2013SLK", form["amountSLK"].value))
                                """if user properly logged in, see if he checked the box for this model"""
                                """if box is checked, modify price using billing, the name of the model and the amount"""
                        if (form.has_key('checkboxSLS') and form["checkboxSLS"].value=="on"):
                                SLSPrice=int(billing("2013SLS", form["amountSLS"].value))
                        if (form.has_key('checkboxAventador') and form["checkboxAventador"].value!=""):
                                aventPrice=int(billing("aventador", form["amountAventador"].value))
		else:
			print "<p>Error!<p>"
                print "<h4>%s's bill:</h4><BR>" % (form["username"].value)
                totalPrice=SLKPrice+SLSPrice+aventPrice
                GST=totalPrice*0.05
                QST=(totalPrice+GST)*0.095
                taxes=GST+QST
                priceWithTax=totalPrice+taxes
                """calculating taxes and the total price"""
                print "<p>Purchases: %s $</p><BR>" % totalPrice
                print "<p>GST: %s $</p><BR>" % GST
                print "<p>QST: %s $</p><BR><BR>" % QST
                print "<p>Total Taxes: %s $</p><BR><BR>" % taxes
                print "<p>Total Amount Due: %s $</p><BR><BR>" % priceWithTax
		print "<p>Thank you for your purchase!</p><BR><BR>"
                appendAmount(form["username"].value, totalPrice)
        else:
                print "<h1>ERROR!</h1>"
	print """__________________________________________________________________________________<BR><BR>"""
        print """Go back to the <a href="http://cs.mcgill.ca/~agebai/homepage.htm">Homepage</a><BR>"""
        print """Go back to the <a href="http://cs.mcgill.ca/~agebai/CATALOGUE.htm">Web Catalogue</a><BR>"""
	print "</body>"


main()
