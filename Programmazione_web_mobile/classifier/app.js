const bayes = require('bayes')

let classifier = bayes();


learn(classifier, 'ciao', 'presentation')
categorize(classifier, 'ciao')


var stateJson = classifier.toJson()
console.log(stateJson);


async function learn(classifier, text, category) {
    return await classifier.learn(text, category)
    
}

async function categorize(classifier, text) {
    return await classifier.categorize(text)
}