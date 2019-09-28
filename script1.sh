if [ $# -eq 0 ]; then
    echo "Please provide file path"
    exit 1
fi

for file in $1/*
do
    if [[ $file == *"."* ]]; then
        echo $(basename $file)
    fi
done