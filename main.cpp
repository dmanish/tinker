import uuid
import random
import string


def get_uuid():
    return uuid.uuid4()


def get_name():
    return "".join(random.choices(string.ascii_lowercase + string.digits, k=16))


def get_client_id():
    return "".join(random.choices(string.digits, k=8))


# Resulting values can't go higher than this number
MAX_VALUE = 16777215

# These are the values that are already defined
# We cannot collide with these values
# The values start at 1,000,000 and go through 1,500,000
defined_values = [i + 1000000 for i in range(500000)]

# Create an algorithm to derive another 500,000 integers using the following inputs
# This integer cannot collide with any value in defined_values
# They also cannot collide with each other
# Every derived value must be unique
# The derived values must be between 1 and MAX_VALUE
# valid range =  0 -1000000 && 1500001 - ( MAX_VALUE - 500000)
for i in range(500000):
    id = get_uuid()
    id_int = int(id.int)
    name = get_name()
    client_id = get_client_id()  

    hash_value = sha256(i  );
    hash_value = hash_value % MAX_VALUE; # MAX_VALUE - 500000
    # if there is a collision then we need to rehash the value
    while hash_value in range(1000000,500000):
        hash_value = sha256(hash_value);
        hash_value = hash_value % MAX_VALUE;  ## MAX_VALUE - 500000


    print(f"{id_int},{name},{client_id},{hash_value}")

    #if colloision i will pick random value from range MAX_VALUE - 500000 to MAX_VALUE
    #possibility of collision is  500000/MAX_VALUE ~ 0.1%