
import requests

print "Retreiving data ..."

lines = requests.get("https://raw.githubusercontent.com/pciutils/pciids/master/pci.ids").text.split('\n')
devices = {}

vendor = ""
final = []

print "Parsing raw data ..."

for line in lines:
	if len(line) > 1 and not line[0] in "#C":
		if line[0] == '\t' and line[1] == '\t': continue
		elif line[0] == '\t': devices[vendor].append(line[1: len(line)])
		
		else:
			vendor = line[0: len(line)]
			devices[vendor] = []

print "Creating descriptors for all vendors (%d) ..." % (len(devices))

for vendor in devices:
	vendor_tuple = tuple(vendor.split("  "))
	
	print "\tCreating descriptors for all %s products (%s) ..." % (vendor_tuple[1], len(devices[vendor]))
	products = []
	
	for product in devices[vendor]:
		product_tuple = tuple(product.split("  "))
		
		products.append({
			"id": int(product_tuple[0], 16),
			"name": product_tuple[1].replace('\\', "\\\\").replace('"', ''.join(['\\', '\"'])),
			
		})
	
	final.append({
		"id": int(vendor_tuple[0], 16),
		"name": vendor_tuple[1].replace('\\', "\\\\").replace('"', ''.join(['\\', '\"'])),
		
		"product_count": len(devices[vendor]),
		"products": products,
		
	})

print "Creating database.h ..."

header = "#define PCI_DATABASE_CREATED 1\n"
i = 0

for vendor in final:
	if vendor["product_count"] == 0: header = "%s\npci_vendors[0x%x].id=0x%x;pci_vendors[0x%x].name=\"%s\";pci_vendors[0x%x].product_count=0;" % (header, i, vendor["id"], i, vendor["name"], i)
	else: header = "%s\npci_vendors[0x%x].id=0x%x;pci_vendors[0x%x].name=\"%s\";pci_vendors[0x%x].product_count=0x%x;pci_vendors[0x%x].products=(pci_product_t*)malloc(0x%x*sizeof(pci_product_t));" % (header, i, vendor["id"], i, vendor["name"], i, vendor["product_count"], i, vendor["product_count"])
	
	j = 0
	
	for product in vendor["products"]:
		header = "%s\n\tpci_vendors[0x%x].products[0x%x].id=0x%x;pci_vendors[0x%x].products[0x%x].name=\"%s\";" % (header, i, j, product["id"], i, j, product["name"])
		j += 1
	
	i += 1

print "Encoding database to UTF-8 ..."
header = header.encode("utf-8")

print "Writing to database.h ..."

database_h = open("database.h", "wb")
database_h.write(header)
database_h.close()

print "Creating vendor_count.h ..."

database_h = open("vendor_count.h", "wb")
database_h.write("#define PCI_VENDOR_COUNT 0x%x" % (len(final)))
database_h.close()

print "Done."
