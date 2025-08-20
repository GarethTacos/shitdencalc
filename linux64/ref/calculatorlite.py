
import math, cmath, statistics, time, os, webbrowser, random, base64
print("   _____ __    _ __      __           ______      __    \n  / ___// /_  (_) /_____/ /__  ____  / ____/___ _/ /____\n  \\__ \\/ __ \\/ / __/ __  / _ \\/ __ \\/ /   / __ `/ / ___/\n ___/ / / / / / /_/ /_/ /  __/ / / / /___/ /_/ / / /__  \n/____/_/ /_/_/\\__/\\__,_/\\___/_/ /_/\\____/\\__,_/_/\\___/ ")
time.sleep(1.5)
def clearscreen():
    if os.name == 'nt': #windows only
        os.system('cls')
    else: #other OSs
        os.system('clear')
def endfunc():
    input("Press Enter to return to main menu.")
    clearscreen()
clearscreen()
while True:
    mainmode = input("┌─┬───────────────────────┐\n│1│Basic Arithmetic       │\n│2│Scientific Calculations│\n│3│Trigonometry           │\n│4│Base Converter         │\n│5│Encrypt / Decrypter    │\n│6│Word Problems          │\n│7│Statistics             │\n│8│Random Number Generator│\n├─┼───────────────────────┤\n│f│Formulae               │\n│a│About                  │\n│q│Quit                   │\n└─┴───────────────────────┘\n")
    if mainmode == '1':
        submode = input("\n1│Addition\n2│Subtraction\n3│Multiplication\n4│Division\n5│Sum\n ├────────────────\n6│Back to Main Menu\n")
        if submode == '1':
            a = float(input("Enter first number: "))
            b = float(input("Enter second number: "))
            result = a + b
            print("result:", result)
            endfunc()
        elif submode == '2':
            a = float(input("Enter first number: "))
            b = float(input("Enter second number: "))
            result = a - b
            print("result:", result)
            endfunc()
        elif submode == '3':
            a = float(input("Enter first number: "))
            b = float(input("Enter multiplier: "))
            result = a * b
            print("result:", result)
            endfunc()
        elif submode == '4':
            a = float(input("Enter number: "))
            b = float(input("Enter dividend: "))
            result = a / b
            print("result:", result)
            iendfunc()
        elif submode == '5':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            result = sum(data)
            print("sum:", result)
            endfunc()
        elif submode == '6':
            clearscreen()
            continue
        else:
            print("Error: not valid function")
    elif mainmode == '2':
        submode = input("\n 1│Exponent\n 2│Logarithm\n 3│Natural log\n 4│nth root\n 5│Phythagoras\' Theorem\n 6│Radians to Degrees\n 7│Degrees to Radians\n 8│Factorial\n 9│Linear Equation Solver\n10│Quadratic Equation Solver\n11│Discriminant\n12│nCr\n13│nPr\n  ├────────────────\n14│Back to Main Menu\n")
        if submode == '1':
            a = float(input("Enter number: "))
            b = float(input("Enter exponent: "))
            result = a ** b
            print("Result:", result)
            endfunc()
        elif submode == '2':
            a = float(input("Enter number: "))
            b = float(input("Enter base of logarithm: "))
            result = math.log(a, b)
            print("Result:", result)
            endfunc()
        elif submode == '3':
            a = float(input("Enter number: "))
            result = math.log1p(a)
            print("Result:", result)
            endfunc()
        elif submode == '4':
            a = float(input("Enter number: "))
            b = float(input("Enter nth root"))
            result = a ** (1/b)
            print("Result:", result)
            endfunc()
        elif submode == '5':
            a = float(input("Enter horizonal change: "))
            b = float(input("Enter vertical change: "))
            result = math.sqrt((a ** 2) + (b ** 2))
            print("Diagonal length:", result)
            endfunc()
        elif submode == '6':
            a = float(input("Enter angle in math.radians"))
            result = math.degrees(a)
            print("result:", result + "°")
            endfunc()
        elif submode == '7':
            a = float(input("Enter angle in degrees: "))
            result = math.radians(a)
            print("result:", result, "math.radians")
            endfunc()
        elif submode == '8':
            a = float(input("Enter number: "))
            result = math.factorial(a)
            print("result:", result)
            endfunc()
        elif submode == '9':
            a = float(input("Enter x term: "))
            b = float(input("Enter constant: "))
            result = (b * -1) / a
            print("result:", result)
            endfunc()
        elif submode == '10':
            a = float(input("Enter x² term: "))
            b = float(input("Enter x term: "))
            d = float(input("Enter constant: "))
            discriminant = (b ** 2) - (4 * a * d)
            result1 = ((b * -1) + cmath.sqrt(discriminant)) / (a * 2)
            result2 = ((b * -1) - cmath.sqrt(discriminant)) / (a * 2)
            print("result:", result1, ",", result2)
            endfunc()
        elif submode == '11':
            a = float(input("Enter x² term: "))
            b = float(input("Enter x term: "))
            d = float(input("enter constant: "))
            result = (b ** 2) - (4 * a * d)
            print("result:", result)
            endfunc()
        elif submode == '12':
            a = int(input("Enter number of items: "))
            b = int(input("Enter number of items choosen: "))
            result = math.comb(a, b)
            print("result:", int(result))
            endfunc()
        elif submode == '13':
            a = int(input("Enter number of items: "))
            b = int(input("Enter number of items choosen: "))
            result = math.perm(a, b)
            print("result:", int(result))
            endfunc()
        elif submode == '14':
            clearscreen()
            continue
        else:
            print("Error: not valid function")
    elif mainmode == '3':
        submode = input("\n 1│Sine\n 2│Cosine\n 3│Tangent\n 4│Inverse Sine\n 5│Inverse Cosine\n 6│Inverse Tangent\n  ├────────────────\n 7│Hyperbolic Sine\n 8│Hyperbolic Cosine\n 9│Hyperbolic Tangent\n10│Hyperbolic Inverse Sine\n11│Hyperbolic Inverse Cosine\n12│Hyperbolic Inverse Tangent\n  ├────────────────\n13│Back to Main Menu\n")
        if submode == '1':
            a = float(input("Enter angle in degrees: "))
            if a == 30:
                result = 0.5
            elif a == 45:
                result = "1/√2"
            elif a == 60:
                result = "√3/2"
            else:
                a = math.radians(a)
                result = round(math.sin(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '2':
            a = float(input("Enter angle in degrees: "))
            if a == 30:
                result = "√3/2"
            elif a == 45:
                result = "1/√2"
            elif a == 60:
                result = 0.5
            else:
                a = math.radians(a)
                result = round(math.cos(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '3':
            a = float(input("Enter angle in degrees: "))
            if a == 30:
                result = "1/√3"
            elif a == 45:
                result = 1
            elif a == 60:
                result = "√3"
            else:
                a = math.radians(a)
                result = round(math.tan(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '4':
            a = float(input("Enter number: "))
            if a == 0.5:
                result = 30
            else:
                a = math.asin(a)
                result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')
            endfunc()
        elif submode == '5':
            a = float(input("Enter number: "))
            if a == 0.5:
                result = 60
            else:
                a = math.acos(a)
                result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')
            endfunc()
        elif submode == '6':
            a = float(input("Enter number: "))
            if a == 1:
                result = 45
            else:
                a = math.atan(a)
                result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')
            endfunc()
        elif submode == '7':
            a = float(input("Enter angle in degrees: "))
            a = math.radians(a)
            result = round(math.sinh(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '8':
            a = float(input("Enter angle in degrees: "))
            a = math.radians(a)
            result = round(math.cosh(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '9':
            a = float(input("Enter angle in degrees: "))
            a = math.radians(a)
            result = round(math.tanh(a), 5)
            print("result:", result)
            endfunc()
        elif submode == '10':
            a = float(input("Enter number: "))
            a = math.asinh(a)
            result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')
            endfunc()
        elif submode == '11':
            a = float(input("Enter number: "))
            a = math.acosh(a)
            result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')

            endfunc()
        elif submode == '12':
            a = float(input("Enter number: "))
            a = math.atanh(a)
            result = round(math.degrees(a), 2)
            print("Angle:", str(result) + '°')
            endfunc()
        elif submode == '13':
            clearscreen()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == '4':
        submode = input("\n1│Denary to Binary\n2│Denary to Hex\n3│Binary to Denary\n4│Binary to Hex\n5│Hex to Denary\n6│Hex to Binary\n ├────────────────\n7│Back to Main Menu\n")
        if submode == '1':
            a = int(input("Enter number to be converted: "))
            result = bin(a)[2:]
            print("result:", result)
            endfunc()
        elif submode == '2':
            a = int(input("Enter number to be converted: "))
            result = hex(a)[2:]
            print("result:", result)
            endfunc()
        elif submode == '3':
            a = input("Enter number to be converted: ")
            result = int(a, 2)
            print("result:", result)
            endfunc()
        elif submode == '4':
            a = input("Enter number to be converted: ")
            a = int(a, 2)
            result = hex(a)[2:]
            print("result:", result)
            endfunc()
        elif submode == '5':
            a = input("Enter number to be converted: ")
            result = int(a ,16)
            print("result:", result)
            endfunc()
        elif submode == '6':
            a = input("Enter number to be converted: ")
            a = int(a ,16)
            result = bin(a)[2:]
            print("result:", result)
            endfunc()
        elif submode == '7':
            clearscreen()
            continue
    elif mainmode == '5':
        print("\nALL ENCODINGS ARE IN UTF-8\nTEXT IS IN BETWEEN b'_______'!!!")
        submode = input("\n1│Text to Standard Base64\n2│Text to URL safe Base64\n3│Text to Base32\n4│Text to Base16\n ├────────────────\n5│Standard Base64 to Text\n6│URL safe Base64 to Text\n7│Base32 to Text\n8│Base16 to Text\n ├────────────────\n9│Back to Main Menu\n")
        if submode == '1':
            a = str(input("Enter text to be encoded: "))
            a = a.encode('utf-8')
            a = base64.standard_b64encode(a)
            print("Base64:", result)
            endfunc()
        elif submode == '2':
            a = str(input("Enter base64 to be encoded: "))
            a = a.encode('utf-8')
            result = base64.urlsafe_b64encode(a)
            print("Base64:", result)
            endfunc()
        elif submode == '3':
            a = str(input("Enter text to be encoded: "))
            a = a.encode('utf-8')
            result = base64.b32encode(a)
            print("Base32:", result)
            endfunc()
        elif submode == '4':
            a = str(input("Enter base64 to be encoded: "))
            a = a.encode('utf-8')
            result = base64.b16encode(a)
            print("Base16:", result)
            endfunc()
        elif submode == '5':
            a = input("Enter text to be decoded: ")
            a = base64.standard_b64decode(a)
            result = a.decode('utf-8')
            print("Text:", result)
            endfunc()
        elif submode == '6':
            a = input("Enter base64 to be decoded: ")
            a = base64.urlsafe_b64decode(a)
            result = a.decode('utf-8')
            print("Text:", result)
            endfunc()
        elif submode == '7':
            a = input("Enter text to be decoded: ")
            a = base64.b32decode(a)
            result = a.decode('utf-8')
            print("Text:", result)
            endfunc()
        elif submode == '8':
            a = input("Enter base64 to be decoded: ")
            a = base64.b16decode(a)
            result = a.decode('utf-8')
            print("Text:", result)
            endfunc()
        elif submode == '9':
            clearscreen()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == '6':
        submode = input("\n1│Compound Interest - Total Amount\n2│Compound Interest - Interest\n3│Area of Triangle\n4│Area of Circle\n ├────────────────\n5│Back to Main Menu\n")
        if submode == '1':
            a = float(input("Enter original amount: "))
            b = float(input("Enter interest rate: "))
            c = float(input("Enter number of terms used: "))
            result = a * ((1 + (b / 100)) ** c)
            print("total amount: $" + str(round(result, 2)))
            endfunc()
        elif submode == '2':
            a = float(input("Enter original amount: "))
            b = float(input("Enter interest rate: "))
            c = float(input("Enter number of terms used: "))
            result = (a * ((1 + (b / 100)) ** c)) - a
            print("interest: $" + str(round(result, 2)))
            endfunc()
        elif submode == '3':
            a = float(input("Enter side 1: "))
            b = float(input("Enter side 2: "))
            c = float(input("Enter angle between sides in degrees: "))
            c = math.radians(c)
            result = (a * b * math.sin(c))/ 2
            print("Area: ", round(result, 5))
            endfunc()
        elif submode == '4':
            a = float(input("Enter radius: "))
            result = math.pi * (a ** 2)
            print("Area: ", round(result, 5))
            endfunc()
        elif submode == '5':
            clearscreen()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == '7':
        submode = input("\n1│Mean\n2│Median\n3│Mode\n4│Standard Deviation\n5│Variance\n ├────────────────\n6│Back to Main Menu\n")
        if submode == '1':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            result = statistics.mean(data)
            print("Mean:", result)
            endfunc()
        elif submode == '2':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            result = statistics.median(data)
            print("Median:", result)
            endfunc()
        elif submode == '3':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            try:
                result = statistics.mode(data)
                print("Mode:", result)
            except statistics.StatisticsError:
                result = 0
                print("There is no mode.")
            endfunc()
        elif submode == '4':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            a = input("Is this a sample or the entire population?\n1│Sample\n2│Population\n")
            if "sample" in a.lower() or a == "1":
                try:
                    result = statistics.stdev(data)
                    print("Standard Deviation:", result)
                except statistics.StatisticsError:
                    result = 0
                    print("There is no Standard Deviation")
            elif "population" in a.lower() or a == '2':
                try:
                    result = statistics.pstdev(data)
                    print("Standard Deviation:", result)
                except statistics.StatisticsError:
                    result = 0
                    print("There is no Standard Deviation.")
            else:
                print("Error: not valid function")
            endfunc()
        elif submode == '5':
            data = list(map(float, input("Enter numbers separated by spaces: ").split()))
            a = input("Is this a sample or the entire population?\n1│Sample\n2│Population\n")
            if "sample" in a.lower() or a == '1':
                try:
                    result = statistics.variance(data)
                    print("Variance:", result)
                except statistics.StatisticsError:
                    result = 0
                    print("There is no Variance.")
            elif "population" in a.lower() or a == '2':
                try:
                    result = statistics.pvariance(data)
                    print("Variance:", result)
                except statistics.StatisticsError:
                    result = 0
                    print("There is no Variance.")
            else:
                print("Error: not valid function")
            endfunc()
        elif submode == '6':
            clearscreen()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == '8':
        submode = input("\n1│Random Floating Point\n2│Random Integers\n ├────────────────\n3│Back to Main Menu\n")
        if submode == '1':
            c = int(input("Enter number of numbers needed: "))
            a = int(input("Enter mininum: "))
            b = int(input("Enter maximum: "))
            for i in range(c):
                result = random.uniform(a, b)
                print(str(i+1) + "|" + str(result))
            endfunc()
        elif submode == '2':
            c = int(input("Enter number of numbers needed: "))
            a = int(input("Enter mininum: "))
            b = int(input("Enter maximum: "))
            for i in range(c):
                result = random.randint(a, b)
                print(str(i+1) + "|" + str(result))
            endfunc()
        elif submode == '3':
            clearscreen()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == 'f':
        submode = input("\n1│Quadratic Equation\n2│Compound Interest\n3│3D Mensuration\n4│Circle Mensuration\n5│E Math Trigonometry\n6│A Math Trigonometry\n ├────────────────\n7│Back to Main Menu\n")
        if submode == '1':
            print("x = -b±√(b²-4ac) / 2a")
            endfunc()
        elif submode == '2':
            print("total amount = P(1+ r/100)ⁿ")
            endfunc()
        elif submode == '3':
            print("Curved surface area of cone = πrl\nSurface area of sphere = 4πr²\nVolume of a cone = 1/3 πr²h\nVolume of sphere = 4/3 πr³")
            endfunc()
        elif submode == '4':
            print("when θ is in radians,\nArc length = rθ\nSector area = 1/2 r²θ")
            endfunc()
        elif submode == '5':
            print("Area of triangle ABC = 1/2 ab sin C\nSine law : a/sin A = b/sin B = c/sin C\nCosine law: a²=b²+c²-2bc cos A")
            endfunc()
        elif submode == '6':
            print("sin²A + cos²A = 1\n\nsec²A = 1 + tan²A\ncosec²A = 1 + cot²A\n\nsin(A±B) = sinA cosB ± cosA sinB\ncos(A±B) = cosA cosB ∓ sinA sinB\ntan(A±B) = tanA±tanB/1∓tanA tanB\n\nsin2A = 2 sinA cosA\ncos2A = cos²A - sin²A = 2cos²A - 1 - 2sin²A\ntan2A = 2tanA / 1 - tan²A")
            endfunc()
        elif submode == '7':
            endfunc()
            continue 
        else:
            print("Error: not valid function")
    elif mainmode == 'a':
        print("Shitden Calculator Beta 3.5\nReccomended for Python 3.13\n")
        endfunc()
        continue
    elif mainmode == 'q':
        print("Goodbye")
        time.sleep(1)
        break
    elif mainmode == '88':
        print("OMG")
        time.sleep(1)
        print("88☆彡 mentioned!!!!")
        time.sleep(1.5)
        webbrowser.open("https://youtube.com/watch?si=HR7YldLq8PcUCOsQ&v=giOsLry_orw")
        time.sleep(5)
        clearscreen()
        continue
    elif mainmode == '1003':
        print("瑞希！")
        time.sleep(2)
        print("ごめん...")
        time.sleep(3)
        webbrowser.open("https://youtube.com/watch?si=rV7RwFx2gqNg9bHC&v=UFRIsspP9UE")
        time.sleep(5)
        clearscreen()
        continue
    else:
        clearscreen()
        continue
## a,b,d,g are variables
